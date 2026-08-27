# Embeddings and Representation Geometry

Tokenization produces arbitrary vocabulary indices. Embeddings are the learned interface that turns those indices into continuous vectors the network can compute with.

## From an ID to a vector

Let the vocabulary size be \(V\) and the model hidden size be \(d\). The token embedding table is

\[
E \in \mathbb{R}^{V\times d}.
\]

For token ID \(i\), embedding lookup selects one row:

\[
x = E[i].
\]

For a sequence of \(T\) tokens:

\[
(i_0,i_1,\ldots,i_{T-1})
\longrightarrow
X_0 =
\begin{bmatrix}
E[i_0]\\
E[i_1]\\
\vdots\\
E[i_{T-1}]
\end{bmatrix}
\in \mathbb{R}^{T\times d}.
\]

The token ID is only an address into the table. Semantic structure begins in the learned vectors, not in the integer values of the IDs.

## Where the geometry comes from

The embedding vectors are model parameters. They are initialized without human-readable meanings and updated by gradient descent along with the rest of the network.

If moving the vector for a token makes next-token predictions better across many training examples, the optimizer receives pressure to move it. Repeated over enormous data, tokens used in related predictive contexts often acquire useful geometric relationships.

That does **not** mean the vector contains a dictionary definition. A better mental model is:

> An embedding is a learned coordinate that makes the downstream computation easier.

The useful structure is distributed across dimensions and interacts with all later weights.

## Minimal vector geometry

For vectors \(a,b\in\mathbb{R}^d\), the dot product is

\[
a\cdot b = \sum_k a_k b_k.
\]

The Euclidean norm is

\[
\|a\|=\sqrt{\sum_k a_k^2}.
\]

Cosine similarity compares direction while factoring out magnitude:

\[
\mathrm{cos}(a,b)=\frac{a\cdot b}{\|a\|\|b\|}.
\]

These operations are useful probes of representation geometry, and dot products are directly used inside attention. But cosine similarity is not "the model's semantic metric." Real representations can be anisotropic, information can live in subspaces or combinations of directions, and downstream nonlinear transformations matter.

## Initial embeddings are not contextual

Before the transformer stack processes the sequence, the same token ID selects the same embedding row regardless of surrounding text.

The initial vector for `bank` is therefore the same lookup in:

```text
river bank
central bank
```

Later hidden states need not be the same. Attention and MLP layers update each position based on context, so the representation becomes contextual.

This distinction is fundamental:

```text
vocabulary embedding
    fixed for a token ID
          |
          v
transformer layers
          |
          v
contextual hidden representation
    depends on token + position + context
```

## The residual stream

It is useful to stop thinking of a transformer as repeatedly creating unrelated embeddings. After the initial embedding stage, each token position has a hidden vector of width \(d\). The transformer stack carries those vectors through a **residual stream** and repeatedly adds learned updates.

Conceptually:

\[
X^{(0)} \rightarrow X^{(1)} \rightarrow \cdots \rightarrow X^{(L)},
\]

with each \(X^{(\ell)}\in\mathbb{R}^{T\times d}\).

The meaning of a position is therefore not stored in one static embedding. It is progressively represented by the evolving hidden state. See [Transformer Block and Residual Stream](../transformers/transformer-block.md).

## From vector space back to vocabulary space

At the output side, the model must turn a final hidden vector \(h\in\mathbb{R}^d\) into one score for every possible next token.

An output projection, usually called the `lm_head`, computes

\[
z = W_{out}h + b
\]

where

\[
z\in\mathbb{R}^{V}.
\]

Each element \(z_j\) is a **logit** for vocabulary item \(j\). The conceptual symmetry is useful:

```text
input:   token ID  -> select one vocabulary row -> hidden vector
output:  hidden vector -> score every vocabulary row -> logits
```

Some architectures tie the input embedding matrix and output projection weights. This is called **weight tying**. The exact matrix convention differs by implementation, but the conceptual relationship is the same.

## Softmax is the probability bridge

Given logits \(z\), softmax produces a normalized distribution:

\[
p_j=\frac{e^{z_j}}{\sum_k e^{z_k}}.
\]

The neural network itself produces scores; a decoding rule later decides how to turn those scores into the next token. Greedy decoding, temperature, top-k, and top-p are inference choices rather than properties of the embedding table.

## Representation geometry is richer than nearest neighbors

Nearest-neighbor examples are intuitive, but several caveats matter when moving from toy vectors to real models:

- a direction can encode a feature without nearby tokens being obvious synonyms;
- several unrelated features can share dimensions or subspaces;
- useful geometry can change substantially across layers;
- different contexts produce different hidden vectors for the same token;
- a linear probe can reveal information that is not obvious from raw cosine distance;
- a feature can be represented by a distributed pattern rather than a single coordinate.

This is why modern interpretability work often studies directions, subspaces, activations, probes, sparse features, and residual-stream updates rather than only static embedding neighborhoods.

## Shape and parameter consequences

The input embedding table contains roughly \(V\times d\) learned values. A larger vocabulary can reduce sequence length for some text but increases vocabulary-sized parameter matrices and makes the output softmax/projection wider.

That is a useful architectural tradeoff, but in large models the dominant parameter count may lie elsewhere, especially in MLPs or MoE experts.

## Connection to the transformer

After token embeddings and positional information establish the initial hidden state, transformer blocks perform two broad operations repeatedly:

- **attention** moves information between token positions;
- **MLPs** transform the features at each position.

Residual connections preserve a shared representational workspace while those updates accumulate. Positional mechanisms determine how order and distance affect the interactions.
