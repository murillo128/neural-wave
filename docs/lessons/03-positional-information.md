# 03 - Positional Information

## Goal

Understand why token identity is not enough. The model also needs information about where each token appears.

## Why this matters

Token embeddings encode identity but not order. The sentences `dog bites man` and `man bites dog` contain the same token embeddings in different positions, but they mean different things.

Language, code, and instructions depend on order.

## Conceptual explanation

After embedding lookup, each token has a vector. But without positional information, the vector for `dog` is the same learned row wherever `dog` appears.

A simple solution is absolute positional embeddings: a learned table with one vector per position.

\[
P \in \mathbb{R}^{max\_context\_size \times hidden\_size}
\]

For each token:

\[
X_i = E(token_i) + P(i)
\]

The sequence shape remains:

\[
X \in \mathbb{R}^{T \times hidden\_size}
\]

## Minimal math

Both vectors have length `hidden_size`:

```text
E(token_i): hidden_size
P(i):       hidden_size
X_i:        hidden_size
```

Addition is component-wise, so the output vector has the same width:

```text
[a, b, c] + [p, q, r] = [a+p, b+q, c+r]
```

There is still one vector per token. The number of rows remains \(T\), and the number of columns remains \(hidden\_size\).

## Visual / geometric intuition

| token | token id | token embedding | position | positional embedding | final vector |
| --- | ---: | --- | ---: | --- | --- |
| dog | 0 | \(E(dog)\) | 0 | \(P(0)\) | \(E(dog) + P(0)\) |
| bites | 1 | \(E(bites)\) | 1 | \(P(1)\) | \(E(bites) + P(1)\) |
| man | 2 | \(E(man)\) | 2 | \(P(2)\) | \(E(man) + P(2)\) |

A token embedding answers:

```text
What token is this?
```

A positional embedding answers:

```text
Where is it in the sequence?
```

Their sum gives a first input vector that answers:

```text
What token is this, and where did it appear?
```

## Implementation model

A simplified implementation performs two lookups and one vector addition for each token:

```cpp
std::vector<double> token = token_embedding_table[token_id];
std::vector<double> position = position_embedding_table[i];
std::vector<double> x_i = add(token, position);
```

The final input matrix has one row per token.

## Learned absolute positional embeddings

Learned absolute positional embeddings are model parameters:

- initialized like other weights;
- updated during training;
- not manually assigned meanings like "first", "second", or "third";
- learned because they reduce prediction error.

This repo is not covering the training loop yet. For now, treat \(P\) as a learned lookup table.

## Practical impact

Position matters because:

- `dog bites man` and `man bites dog` differ;
- function argument order matters in code;
- punctuation location can change interpretation;
- earlier and later prompt instructions may play different roles.

In this simplified absolute-position view, \(P(4096)\) may not exist if `max_context_size` is 4096 positions. Applications may reject, truncate, chunk, summarize, or retrieve. This motivates later long-context techniques.

Modern models often use other positional schemes, including RoPE. RoPE is only future motivation here; this lesson does not explain RoPE math.

## Lab walkthrough

Run the [Positional Embeddings Lab](../labs/03-positional-embeddings.md) in `labs/03-positional-embeddings/`.

The lab demonstrates:

- same token embedding;
- different positional embedding;
- different final input vector;
- no attention yet.

## Common confusions

### Does adding position create a bigger vector?

No. Both vectors have length `hidden_size`, and addition is component-wise.

### Does position alone explain sentence meaning?

No. Position tells the model where tokens appear. Later layers are needed for tokens to influence each other.

### Are position vectors manually designed?

In the lab, yes, for teaching. In learned absolute positional embeddings, they are trained parameters.

## Bridge to Lesson 04: from token+position vectors to contextual vectors

After this lesson, each row knows:

\[
token\ identity + position
\]

But each row is still not fully contextual.

The next question is:

How does the vector for one token become influenced by the other tokens?

That is the outside view of a transformer block.

## Boundaries

This lesson intentionally stops before transformer internals:

- no attention internals;
- no Q/K/V;
- no KV cache internals;
- no RoPE math;
- no training loop.

## Session summary

### 1. Concepts learned

- Token embeddings encode identity but not order.
- Positional information tells the model where each token appears.
- Absolute positional embeddings can be modeled as a learned position table.
- \(X_i = E(token_i) + P(i)\) combines token identity and position.
- The sequence shape remains \(T \times hidden\_size\).

### 2. Open questions

- How do token+position vectors become contextual?
- What does a transformer block do from the outside?

### 3. Next concrete step

Read the Lesson 04 stub: transformer block from the outside.

### 4. Repo changes

- Moved the positional information lesson into `docs/lessons/`.
- Connected the lesson to the C++ positional embeddings lab.
