# 02 - Embeddings

## Goal

Understand how arbitrary token IDs become vectors that a model can process.

The key operation is embedding lookup:

\[
x = E[token\_id]
\]

## Why this matters

Token IDs are arbitrary. The model should not feed raw ID numbers as semantic values. ID `17` is not inherently closer to ID `18` than to ID `9000`.

Embeddings solve this by mapping each token ID to a vector. The vector is the first learned representation of the token.

!!! note "Lookup, not arithmetic on IDs"
    The model uses the token ID to choose a row. It does not treat the ID number itself as a meaningful feature.

## Conceptual explanation

An embedding table is a matrix with one row per vocabulary token:

\[
E \in \mathbb{R}^{vocab\_size \times hidden\_size}
\]

A token ID selects one row:

\[
x = E[token\_id]
\]

For a sequence:

\[
[id_0, id_1, \ldots, id_{T-1}]
\rightarrow
[E[id_0], E[id_1], \ldots, E[id_{T-1}]]
\]

The result is a matrix:

\[
X \in \mathbb{R}^{T \times hidden\_size}
\]

`hidden_size` is the width of each vector. If `hidden_size = 4`, each token is represented by four numbers in this toy example. Real models use much larger widths.

## Minimal math

The dot product compares two vectors component by component:

\[
a \cdot b = \sum_i a_i b_i
\]

The norm is the vector length:

\[
\|a\| = \sqrt{\sum_i a_i^2}
\]

Cosine similarity compares vector direction:

\[
\mathrm{cos}(a,b) =
\frac{a \cdot b}{\|a\|\|b\|}
\]

These tools let us talk about whether two embeddings are close or aligned in the toy lab.

## Visual / geometric intuition

Embeddings are learned coordinates. Related tokens may become close or aligned because that helps prediction during training.

They are not explicit dictionary definitions. The vector for `dog` does not literally store the sentence "a domesticated animal". It stores coordinates that become useful in the model's learned geometry.

Initial token embeddings are also non-contextual. Before later layers process the sequence, the embedding for `dog` is the same row whether the text is `dog bites man` or `man bites dog`.

## Implementation model

In code-like notation:

```text
embedding_table[vocab_size][hidden_size]
```

A lookup is just row selection:

```cpp
std::vector<double> x = embedding_table[token_id];
```

For a sequence, the implementation loops over token IDs and appends one vector per ID.

## Practical impact

Embeddings are the first learned interface between vocabulary IDs and model computation.

They also explain why vocabulary size and hidden size matter for memory:

```text
vocab_size * hidden_size
```

That product appears on the input side in the embedding table and on the output side in the vocabulary projection. Quantization will matter later as a memory/cost topic, but this lesson does not explain quantization internals.

## The `lm_head`: output projection

At the end of the model, a final hidden vector \(h\) must be converted back into scores over the vocabulary.

The output projection, often called `lm_head`, produces one logit per vocabulary token:

\[
logit_j = h \cdot W_{out}[j]
\]

Equivalently, the conceptual loop over vocabulary rows can be written as a matrix multiplication:

\[
logits = h W_{out}^{T}
\]

Conceptually:

- input side: token ID selects one row from the embedding table;
- output side: hidden vector is compared or scored against every vocabulary row;
- the loop over vocabulary is equivalent to a matrix multiplication.

Sometimes the embedding table and output projection share weights. This is called weight tying. It is useful because both are vocab-sized matrices. Details come later.

!!! note "Two directions"
    Embedding lookup maps from a token ID into vector space. The `lm_head` maps from vector space back to vocabulary scores.

## Tiny softmax bridge

Given logits:

\[
[2.0, 1.0, 0.1]
\]

Softmax converts them into probabilities:

\[
p_i = \frac{e^{logit_i}}{\sum_j e^{logit_j}}
\]

This is only enough to connect embeddings, `lm_head`, logits, and probabilities. Decoding and sampling are later topics.

## Lab walkthrough

Run the [Embedding Lookup Lab](../labs/02-embedding-lookup.md) in `labs/02-embedding-lookup/`.

The lab demonstrates:

- token string -> token ID;
- token ID -> vector;
- dot product;
- norm;
- cosine similarity;
- nearest neighbors.

The vectors are manually chosen, not learned.

## Common confusions

### Why not pass token IDs directly?

Because token IDs are arbitrary indices. Feeding them as numeric magnitudes would create fake relationships.

### Does an embedding fully encode meaning?

No. It is an initial learned coordinate. Full contextual meaning requires later layers.

### Is cosine similarity the model's whole understanding?

No. Cosine similarity is a useful geometric probe, not the full model computation.

## Boundaries

This lesson does not explain training, attention, Q/K/V, contextualization, full decoding, or quantization internals.

## Session summary

### 1. Concepts learned

- Token IDs are arbitrary.
- Embedding lookup maps IDs to vectors.
- The embedding table has shape \(vocab\_size \times hidden\_size\).
- A sequence becomes \(T \times hidden\_size\).
- Dot product, norm, and cosine similarity help compare vectors.
- The `lm_head` maps a final hidden vector to logits over the vocabulary.

### 2. Open questions

- Why do embeddings become semantically organized during training?
- How do token vectors become contextual?

### 3. Next concrete step

Read Lesson 03: positional information.

### 4. Lab connection

- The paired lab turns row lookup, dot product, norm, and cosine similarity into executable examples.
- The vectors are intentionally tiny so the geometry stays visible.
