# Transformer Block and Residual Stream

A transformer block is best understood first as a structured update to a sequence of hidden vectors.

If the input has \(T\) token positions and hidden width \(d\), then

\[
X\in\mathbb{R}^{T\times d}
\]

enters the block and a matrix of the same shape usually leaves it:

\[
Y\in\mathbb{R}^{T\times d}.
\]

The values change; the basic sequence shape does not.

## The outside view

A common modern decoder-only, pre-normalization block can be sketched as

\[
A = \mathrm{Attention}(\mathrm{Norm}(X))
\]

\[
X' = X + A
\]

\[
M = \mathrm{MLP}(\mathrm{Norm}(X'))
\]

\[
Y = X' + M.
\]

Architectures vary, but this schematic exposes the main roles:

```text
residual stream X
      |
      +-> norm -> attention -> additive update
      |
      v
residual stream X'
      |
      +-> norm -> MLP -> additive update
      |
      v
residual stream Y
```

The block does not have one monolithic job. Attention, MLPs, normalization, and residual connections solve different problems.

## Residual stream: a shared representational workspace

The **residual stream** is the evolving hidden vector at every token position as it passes through the stack.

A residual connection updates a state as

\[
x \leftarrow x + \Delta x
\]

rather than replacing \(x\) completely.

That creates a useful mental model: each sublayer reads the current representation, computes an update, and writes that update back into a shared workspace.

Across many layers:

\[
X^{(0)} \rightarrow X^{(1)} \rightarrow \cdots \rightarrow X^{(L)}.
\]

Earlier information can remain available while new features are added, removed, amplified, rotated, or combined. This also makes deep networks easier to optimize because each layer can learn a correction around an identity path instead of having to reconstruct the entire representation from scratch.

## Attention: communication across positions

Before attention, every token position has its own vector. Attention is the component that allows one position to read information from other positions.

At a high level, each position creates three learned projections:

- **query (Q)** — what information am I looking for?
- **key (K)** — what kinds of queries should match me?
- **value (V)** — what information should be transferred if I am selected?

Queries are compared with keys, producing attention weights. Those weights determine how values from different positions are combined.

The core pattern is

```text
current representation
   -> Q/K/V projections
   -> compare Q with K
   -> normalize match scores
   -> weighted mixture of V
   -> attention update
```

A deeper pass will formalize

\[
\mathrm{softmax}\left(\frac{QK^T}{\sqrt{d_k}} + \text{mask}\right)V,
\]

but the important first intuition is **routing information according to content-dependent matches**.

### Causal attention

A decoder-only model predicting the next token must not read future tokens. A causal mask therefore restricts position \(i\) to positions at or before \(i\).

During training, many next-token predictions can still be computed in parallel because the mask enforces the dependency structure mathematically. During autoregressive generation, future positions genuinely do not exist yet, so new tokens are produced sequentially in the basic decoding loop.

## MLP: transformation within a position

Attention moves information between positions. The MLP performs a nonlinear transformation independently at each position using the same learned weights.

Conceptually:

```text
position i vector
   -> expand/project features
   -> nonlinearity / gating
   -> project back to hidden size
   -> additive residual update
```

A simple feed-forward form is

\[
\mathrm{MLP}(x)=W_2\,\sigma(W_1x),
\]

while modern LLMs commonly use gated variants such as SwiGLU.

The crucial contrast is:

- **attention** changes a token representation using information from other positions;
- **MLP** changes it using learned feature transformations at that position.

This is why an MLP can hold a large fraction of model parameters even though it does not directly mix tokens.

## Normalization: controlling scale

Deep residual updates can make activation scales drift. Normalization layers such as LayerNorm or RMSNorm rescale hidden states into a better-conditioned regime for the next learned transformation.

A useful first intuition is not "normalization contains knowledge" but:

> normalization keeps the numerical geometry of the residual stream in a range where attention and MLP projections remain trainable and predictable.

Modern decoder LLMs often use RMSNorm and pre-norm layouts, but there are important variants.

## Positional information enters the interaction

Attention based only on token content would still need a way to know order. Position can be added to the residual representation or injected into the attention calculation.

With RoPE, for example, the query/key vectors are rotated according to token position before their dot products are computed. That means position changes which tokens match strongly even when their content features are similar.

See [Positional Information](positional-information.md).

## Why representations become contextual

Suppose the initial representation of `bank` is the same vocabulary embedding in two sentences.

After attention, the `bank` position can read features from nearby words such as `river` or `central`. The MLP can then transform the resulting combined features. Repeating this across layers creates different hidden trajectories:

```text
"river bank"     -> bank representation shaped by river context
"central bank"   -> bank representation shaped by financial context
```

Contextualization is therefore not a separate lookup table. It is the cumulative result of many content-dependent residual updates.

## Multi-head attention

One attention operation does not need to represent every relationship in one similarity space. Multi-head attention uses several sets of projections so different heads can create different matching geometries.

One head might become useful for local syntactic relationships, another for copying or induction-like patterns, another for longer-range dependencies. These descriptions are tendencies, not fixed human-assigned jobs.

Modern architectures may share K/V projections across heads through MQA or GQA to reduce inference memory while retaining many query heads.

## Architectural variations

The conceptual block survives many implementation differences:

- LayerNorm versus RMSNorm;
- sequential versus parallel attention/MLP residual branches;
- standard MLP versus gated MLP;
- dense MLP versus MoE expert routing;
- full multi-head K/V versus GQA/MQA;
- different positional schemes;
- local, sliding-window, sparse, or hybrid attention;
- additional recurrent or state-space components.

The right invariant to keep in mind is not one exact diagram. It is the repeated transformation of a residual representation through mechanisms that **communicate**, **transform**, and **stabilize** information.

## Connection to inference

The transformer block explains several inference concepts later in the map:

- the **KV cache** exists because attention keys and values for previous positions can be reused during decode;
- decode is sequential because each new token changes the context for the next prediction;
- MQA/GQA matter because sharing K/V reduces cache size;
- MoE changes which MLP-like parameters are active for each token;
- hidden size and sequence length determine activation shapes even when parameter storage is elsewhere.

These are consequences of the architecture, not a separate serving theory.

## Connection to the output

After the final transformer layer, a final normalization is commonly applied and the hidden state for the relevant position is projected through the vocabulary head:

\[
h \rightarrow W_{out}h \rightarrow logits.
\]

That closes the core loop:

```text
token IDs
  -> initial representations
  -> repeated contextual residual updates
  -> final hidden state
  -> vocabulary logits
  -> next-token decision
```
