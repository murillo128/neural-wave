# Positional Information

Token identity is not enough to represent a sequence. A language model also needs access to order and distance.

The phrases

```text
dog bites man
man bites dog
```

contain the same token identities but express different relationships. The model therefore needs some mechanism that makes position available to its computation.

## The permutation problem

A token embedding lookup by itself depends only on token ID:

\[
x_i = E[token_i].
\]

Without another source of positional information, swapping two positions would only swap their rows. A pure set-like computation would have no intrinsic notion of "first," "before," or "three tokens ago."

Transformers solve this by injecting position into the representation or into the attention calculation.

## Learned absolute positional embeddings

The simplest teaching model is a learned table

\[
P\in\mathbb{R}^{C\times d}
\]

with one vector for each position up to context size \(C\). The initial representation becomes

\[
x_i = E[token_i] + P[i].
\]

Because both terms have width \(d\), the sequence shape remains

\[
X\in\mathbb{R}^{T\times d}.
\]

This gives an intuitive decomposition:

```text
token embedding  -> what token is here?
position vector   -> where is it?
sum               -> initial token+position representation
```

The positional vectors are learned parameters, not hand-written encodings of concepts such as "first" or "second."

## Sinusoidal position encodings

The original Transformer used deterministic sine/cosine functions at different frequencies rather than a learned table.

The geometric intuition is that position is represented as phase at multiple scales. Short-wavelength dimensions change rapidly with position; long-wavelength dimensions change slowly. A linear transformation can then recover useful relationships between nearby and distant positions.

The important conceptual contrast is:

- learned absolute embeddings store a separate learned vector for each position;
- sinusoidal encodings compute a structured vector from the position index.

Both are added to the token representation in the classic formulation.

## RoPE: position inside attention geometry

Many modern decoder-only LLMs use **Rotary Positional Embeddings (RoPE)** instead of adding an absolute position vector to the residual stream.

RoPE groups query/key coordinates into 2D pairs and rotates each pair by an angle that depends on token position. Conceptually:

\[
q_i' = R(i)q_i, \qquad k_j' = R(j)k_j.
\]

Attention compares the rotated vectors:

\[
q_i'\cdot k_j'.
\]

Because relative rotation depends on the difference between positions \(i\) and \(j\), the dot product naturally carries relative-position information.

A useful visual model is a clock hand. Two vectors may start with a particular orientation, but position rotates their coordinate frame. When attention takes a dot product, the relative angle now contains information about how far apart the positions are.

This is a materially different mechanism from

\[
E[token_i]+P[i].
\]

Both solve the order problem, but they inject position at different points in the computation.

## Attention biases such as ALiBi

Another family leaves token/query/key representations mostly unchanged and adds a position-dependent bias directly to attention scores. ALiBi, for example, penalizes attention to more distant positions with head-dependent slopes.

This gives a useful taxonomy:

```text
position can enter via
  1. the residual representation itself      (absolute/sinusoidal addition)
  2. query/key geometry                       (RoPE)
  3. the attention score                      (relative biases / ALiBi-like methods)
```

Architectures can also combine ideas.

## Position is not context

Knowing position does not by itself make a token representation contextual.

After positional information has been supplied, a row may encode something like "this token is `dog` at position 0," but it still needs attention to incorporate information from `bites` and `man`.

That distinction is important:

```text
token identity + position
          |
          v
attention / transformer layers
          |
          v
context-dependent representation
```

See [Transformer Block and Residual Stream](transformer-block.md).

## Long context is more than increasing a number

With learned absolute embeddings, positions beyond the trained table may literally be undefined. RoPE avoids that exact limitation, but it does not make context extension free.

A model is trained under a distribution of sequence lengths and positional relationships. Extending context can require changing RoPE scaling, retraining or continued training, attention behavior, and inference memory. A model may technically accept a long sequence while using very distant information poorly.

So "context length" has at least two meanings:

- **mechanical capacity** — the sequence length the architecture/runtime accepts;
- **effective long-range capability** — how reliably the trained model uses information at those distances.

## Practical consequences

Positional design influences long-context quality, extrapolation behavior, attention patterns, and how models can be adapted to larger context windows. It also interacts with KV-cache size because every additional context position creates additional attention state during inference.

Those system consequences follow from the mechanism; the core idea remains: **a sequence model needs order, and modern architectures differ mainly in where and how they inject it.**
