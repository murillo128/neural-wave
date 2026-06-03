# 02 - Embeddings: token IDs to vectors

## Goal

Explain how arbitrary token IDs become learned vectors that the model can process.

## Conceptual explanation

Token IDs are arbitrary integers. The number assigned to a token is an index, not a semantic magnitude. A model should not treat token ID `42` as "twice as meaningful" as token ID `21`, or as closer to token ID `43` just because the numbers are adjacent.

An embedding table solves this. It maps token IDs to vectors:

- The embedding table has one row per vocabulary token.
- A token ID selects one row of the table.
- The selected row is the token's embedding vector.
- The vector is learned during training; the ID is just a lookup key.

Embeddings are the first learned layer that turns discrete token IDs into continuous values the rest of the model can process.

## Minimal math

Define:

```text
E = embedding table
x = E[token_id]
```

Dimensions:

- `vocab_size`: number of tokens in the vocabulary.
- `hidden_size`: number of numeric components in each embedding vector.
- `T`: sequence length, measured in tokens.

The embedding table shape is:

```text
E: vocab_size x hidden_size
```

For one token:

```text
token_id = id
x = E[id]
x has shape hidden_size
```

For a sequence:

```text
token_ids = [id0, id1, ..., idT-1]
X = [E[id0], E[id1], ..., E[idT-1]]
X has shape T x hidden_size
```

### Dot product

The dot product multiplies matching components and sums them:

```text
a · b = sum(a_i * b_i)
```

It is a simple way to compare how aligned two vectors are, but it also depends on vector magnitude.

### Norm

The norm is the length of a vector:

```text
||a|| = sqrt(sum(a_i * a_i))
```

### Cosine similarity

Cosine similarity normalizes by the vector lengths:

```text
cos(a, b) = (a · b) / (||a|| * ||b||)
```

Cosine similarity compares direction more than magnitude. Dot product can be affected by both direction and vector length.

## Geometric intuition

Embeddings can be understood as coordinates in a learned vector space. During training, vectors are adjusted so they are useful for next-token prediction.

Example natural-language tokens:

```text
cat, gato, dog, house
```

`cat`, `gato`, and `dog` may become more aligned than `cat` and `house` because they can be useful in similar contexts.

Example code tokens:

```text
std, vector, int, string
```

These may become aligned because they often appear in related programming contexts.

Important cautions:

- Embeddings are not explicit dictionary definitions.
- "Close" is a useful intuition, not a perfect semantic law.
- Initial embeddings are not full contextual meanings.
- The same token starts with the same embedding each time it appears.
- Later layers add context so the representation can depend on surrounding tokens.

## Implementation summary

The lab in `labs/02-embedding-lookup/` demonstrates the core lookup and comparison ideas with small hand-written data.

It implements:

- token string -> token ID
- token ID -> vector
- dot product
- vector norm
- cosine similarity
- nearest neighbors

The vectors are manually chosen for teaching. They are not learned by training.

## Practical impact

Embedding tables can be large because they scale with vocabulary size and hidden size:

```text
embedding_table parameters = vocab_size * hidden_size
memory = vocab_size * hidden_size * bytes_per_parameter
```

Example memory cost for one table with `vocab_size = 50,000` and `hidden_size = 4,096`:

| Numeric format | Bytes per parameter | Approximate memory |
| --- | ---: | ---: |
| FP32 | 4 | 819 MB |
| FP16 / BF16 | 2 | 410 MB |
| INT8 | 1 | 205 MB |
| INT4 | 0.5 | 102 MB |

Quantization is only being mentioned here as a memory-impact topic. The internals are a later topic.

The `lm_head` has a similar shape and cost. It maps a final hidden vector to one raw score per vocabulary token:

```text
logit[token] = h · lm_head[token]
```

If `lm_head` is stored as `vocab_size x hidden_size`, then:

```text
logits = h @ lm_head.T
```

Logits are raw token scores before softmax. Softmax converts logits into probabilities.

Embedding lookup is cheap computationally because it selects rows. The embedding table can still be large in memory. The `lm_head` is also large in memory and has meaningful compute cost during generation because the model scores many possible next tokens.

Vocabulary size affects several trade-offs:

- A larger vocabulary can reduce token count for some workloads.
- A larger vocabulary increases embedding and `lm_head` size.
- Tokenization efficiency, memory, serving cost, and quantization considerations are connected.

Weight tying means the embedding table and `lm_head` can share weights conceptually or in implementation, reducing separate parameter storage.

## Boundaries

This lesson intentionally does not cover later transformer internals:

- Attention is not covered yet.
- Q/K/V are not covered yet.
- KV cache is not covered yet.
- RoPE is not covered yet.
- Quantization is only mentioned as a memory-impact topic.

## Session summary

### 1. Concepts learned

- Token IDs are arbitrary indices.
- Embedding lookup maps token IDs to learned vectors.
- `embedding_table[vocab_size][hidden_size]` describes the table shape.
- `x = E[token_id]` describes one token lookup.
- A sequence of length `T` becomes a `T x hidden_size` matrix.
- Dot product and cosine similarity compare vectors in different ways.
- Embeddings are learned coordinates, not explicit definitions.
- Initial embeddings are not yet contextual.
- `lm_head` maps final hidden vectors to logits over the vocabulary.
- Embedding and `lm_head` parameter counts scale with `vocab_size * hidden_size`.

### 2. Open questions

- How does the model know token order?
- Why are "dog bites man" and "man bites dog" different if they contain the same token embeddings?
- How does an initial embedding become contextual?
- How will later layers let tokens interact?
- What are positional embeddings / positional information?

### 3. Next concrete step

Lesson 03: Positional Information.

### 4. Repo changes

- Added this note for Lesson 02.
- Added `labs/02-embedding-lookup/` as a small C++ embedding lookup lab.
- Updated the learning map, glossary, questions, README, and next-session prompt.
