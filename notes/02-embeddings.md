# 02 - Embeddings: token IDs to vectors

## Goal

Explain how arbitrary token IDs become learned vectors that the model can process.

Lesson 01 ended here:

```text
text -> tokens -> token IDs
```

This lesson adds the next step:

```text
token IDs -> embeddings
```

## Why this matters

Token IDs are useful for lookup, but they are not useful numeric descriptions by themselves. A model needs vectors whose components can be multiplied, added, compared, and transformed.

Embeddings are the bridge from discrete vocabulary IDs to continuous model computation.

## Conceptual explanation

Token IDs are arbitrary integers. The number assigned to a token is an index, not a semantic magnitude. A model should not treat token ID `42` as "twice as meaningful" as token ID `21`, or as closer to token ID `43` just because the numbers are adjacent.

An embedding table solves this:

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

### One token lookup

Suppose:

```text
vocab_size = 5
hidden_size = 3
```

A tiny embedding table might look like this:

| token | token_id | E[token_id] |
| --- | ---: | --- |
| `<pad>` | 0 | `[0.00, 0.00, 0.00]` |
| `cat` | 1 | `[0.90, 0.20, 0.10]` |
| `dog` | 2 | `[0.88, 0.25, 0.12]` |
| `house` | 3 | `[-0.10, 0.05, 0.95]` |
| `.` | 4 | `[0.01, -0.02, 0.03]` |

For one token:

```text
token_id = 2
x = E[2]
x = [0.88, 0.25, 0.12]
x has shape hidden_size = 3
```

The ID `2` is only a row number. The vector is the value used by later computation.

### Sequence lookup

For a sequence of `T = 4` token IDs:

```text
token_ids = [1, 2, 3, 4]
```

lookup produces:

```text
X = [
  E[1],
  E[2],
  E[3],
  E[4]
]
```

With `hidden_size = 3`, the result has shape:

```text
X: T x hidden_size = 4 x 3
```

Visually:

| position | token_id | embedding row |
| ---: | ---: | --- |
| 0 | 1 | `[0.90, 0.20, 0.10]` |
| 1 | 2 | `[0.88, 0.25, 0.12]` |
| 2 | 3 | `[-0.10, 0.05, 0.95]` |
| 3 | 4 | `[0.01, -0.02, 0.03]` |

At this point, each row describes token identity. It does not yet include position or surrounding context.

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

## Input embeddings vs output projection

There are two vocabulary-sized tables that are easy to confuse.

### Input side: token ID selects one row

On the input side, the model receives token IDs. Each ID selects one row from the embedding table:

```text
x = E[token_id]
```

Only the rows for the actual input tokens are looked up.

### Output side: hidden vector scores every vocabulary item

On the output side, the model has a final hidden vector `h` for the current prediction position. The model must score every possible next token in the vocabulary.

Conceptually:

```text
for each vocab token v:
    logit[v] = dot(h, lm_head[v])
```

If `lm_head` is stored as `vocab_size x hidden_size`, the same operation is usually written as matrix multiplication:

```text
logits = h @ lm_head.T
```

The result is:

```text
logits has shape vocab_size
```

So the difference is:

| Side | Input | Operation | Output |
| --- | --- | --- | --- |
| Embedding lookup | one token ID | select one row | one vector of size `hidden_size` |
| Output projection / `lm_head` | one hidden vector `h` | score every vocabulary row | logits vector of size `vocab_size` |

The input side asks, "Which vector represents this token ID?" The output side asks, "How compatible is this hidden vector with every possible next token?"

## Logits and softmax toy example

Logits are raw scores. They are not probabilities yet.

Suppose the vocabulary is:

```text
[cat, dog, house]
```

and the output projection produces:

```text
logits = [2.0, 1.0, 0.0]
```

Softmax converts those scores into a probability distribution:

```text
exp(2.0) = 7.39
exp(1.0) = 2.72
exp(0.0) = 1.00
sum      = 11.11
```

Approximate probabilities:

| token | logit | probability |
| --- | ---: | ---: |
| `cat` | 2.0 | 0.67 |
| `dog` | 1.0 | 0.24 |
| `house` | 0.0 | 0.09 |

The model can then choose a next token. Greedy decoding would choose `cat`. Sampling might choose another token according to the distribution.

This example does not explain how the hidden vector `h` was created. That comes later.

## Implementation summary

The lab in `labs/02-embedding-lookup/` demonstrates the core lookup and comparison ideas with small hand-written data.

It implements:

- token string -> token ID;
- token ID -> vector;
- dot product;
- vector norm;
- cosine similarity;
- nearest neighbors.

The vectors are manually chosen for teaching. They are not learned by training.

The lab's central message is: IDs are arbitrary; vectors carry useful relationships.

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

Quantization is only being mentioned here as a memory/cost teaser. The internals are a later topic.

The `lm_head` has a similar shape and cost. Embedding lookup is cheap computationally because it selects rows. The `lm_head` has meaningful compute cost during generation because it scores many possible next tokens.

Vocabulary size affects several trade-offs:

- A larger vocabulary can reduce token count for some workloads.
- A larger vocabulary increases embedding and `lm_head` size.
- Tokenization efficiency, memory, serving cost, and later quantization considerations are connected.

Weight tying means the embedding table and `lm_head` can share weights conceptually or in implementation, reducing separate parameter storage.

## Boundaries

This lesson intentionally does not cover later transformer internals:

- attention is not covered yet;
- Q/K/V are not covered yet;
- KV cache is not covered yet;
- RoPE is not covered yet;
- quantization is only mentioned as a memory/cost teaser.

## Session summary

### 1. Concepts learned

- Token IDs are arbitrary indices.
- Embedding lookup maps token IDs to learned vectors.
- `embedding_table[vocab_size][hidden_size]` describes the table shape.
- `x = E[token_id]` describes one token lookup.
- A sequence of length `T` becomes a `T x hidden_size` matrix.
- Dot product and cosine similarity compare vectors in different ways.
- Embeddings are learned coordinates, not explicit definitions.
- Initial embeddings are non-contextual.
- The input embedding table selects one row for a token ID.
- The output projection scores every vocabulary token from a hidden vector `h`.
- `lm_head` produces a logits vector of size `vocab_size`.
- Softmax converts logits into a probability distribution.
- Embedding and `lm_head` parameter counts scale with `vocab_size * hidden_size`.

### 2. Open questions

- How does the model know token order?
- Why are `dog bites man` and `man bites dog` different if they contain the same token embeddings?
- How does an initial embedding become contextual?

### 3. Next concrete step

Read Lesson 03, `notes/03-positional-information.md`, and run `labs/03-positional-embeddings/` to see token identity combined with position.

### 4. Repo changes

- Polished `notes/02-embeddings.md` into a more consistent chapter.
- Added clearer one-token and sequence embedding lookup examples.
- Clarified input embeddings versus output projection.
- Added a toy logits and softmax example.
- Connected the lesson more directly to `labs/02-embedding-lookup/`.
