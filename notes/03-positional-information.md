# 03 - Positional information: token identity plus order

## Goal

Understand why token embeddings need positional information before they are passed onward.

Lesson 02 produced one vector per token:

```text
token IDs -> embeddings
```

This lesson adds position:

```text
embeddings + positional information -> token+position vectors
```

After this lesson, each row knows which token it represents and where that token appears. It still does not know the full surrounding context.

## Why this matters

Token embeddings alone identify tokens, but they do not encode order.

These sentences contain the same three tokens:

```text
dog bites man
man bites dog
```

If we only look up token embeddings, the same token has the same starting vector each time it appears. The model needs some way to distinguish `dog` at position `0` from `dog` at position `2`.

Position is what lets the model start representing sequence order.

## Conceptual explanation

A simple positional embedding scheme uses a second table:

```text
P = position embedding table
```

Each position has a vector with the same size as a token embedding. That allows the model input at position `i` to be formed by addition:

```text
X_i = E(token_i) + P(i)
```

Where:

- `E(token_i)` says which token is present;
- `P(i)` says where it appears;
- `X_i` is the vector passed onward for that row.

This is the first place where token identity and sequence order are combined.

## Minimal math

Definitions:

```text
E: token embedding table
P: positional embedding table
T: sequence length
hidden_size: vector width
```

Shapes:

```text
E[token_id] has shape hidden_size
P(i)        has shape hidden_size
X_i         has shape hidden_size
```

For a sequence:

```text
X = [X_0, X_1, ..., X_(T-1)]
X has shape T x hidden_size
```

The shape remains `T x hidden_size` because each row is still one vector per input token. Addition combines information inside each row; it does not add extra rows or widen the vector.

## Visual table

For the sequence:

```text
dog bites man
```

we can visualize the construction like this:

| token | token_id | `E(token)` | position | `P(i)` | `X_i = E(token) + P(i)` |
| --- | ---: | --- | ---: | --- | --- |
| `dog` | 0 | `[1.00, 0.20, -0.10, 0.50]` | 0 | `[0.01, 0.02, 0.03, 0.04]` | `[1.01, 0.22, -0.07, 0.54]` |
| `bites` | 1 | `[0.10, 1.20, 0.30, -0.40]` | 1 | `[0.10, 0.20, 0.30, 0.40]` | `[0.20, 1.40, 0.60, 0.00]` |
| `man` | 2 | `[0.90, -0.30, 0.80, 0.10]` | 2 | `[-0.05, -0.10, -0.15, -0.20]` | `[0.85, -0.40, 0.65, -0.10]` |

The final matrix still has three rows and four columns:

```text
T x hidden_size = 3 x 4
```

## Mental model

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

That is still not the same as contextual meaning. The vector for `dog` at position `0` does not yet know that `bites` follows it or that `man` appears later. It only combines token identity and position.

## Learned absolute positional embeddings

In this simplified lesson, each absolute position has its own learned vector:

```text
P(0), P(1), P(2), ...
```

The position embedding table has shape:

```text
max_context_size x hidden_size
```

Like token embeddings, these vectors are model parameters. They are initialized and then updated during training because useful position vectors help reduce next-token prediction error.

This repo is not covering the training loop yet. For now, treat the position table as a learned lookup table that is added to token embeddings.

## Practical impact

Positional information matters because language is ordered:

- `dog bites man` and `man bites dog` have different meanings.
- Function argument order matters in code.
- Punctuation position can change interpretation.
- Earlier and later instructions can play different roles in prompts.

It also affects model limits. In this simplified absolute-position view, a model has positional vectors up to `max_context_size`. Longer-context methods and modern positional techniques address this differently, but that is a later topic.

RoPE is one modern positional technique. This lesson only uses it as future motivation; it does not introduce RoPE math.

## Implementation summary

The lab in `labs/03-positional-embeddings/` demonstrates:

- token ID lookup;
- token embedding lookup;
- position embedding lookup;
- vector addition;
- final input vectors for two sentences with the same words in different order.

The important observation is:

```text
same token embedding, different final vector because of position
```

For example:

```text
E("dog") + P(0) != E("dog") + P(2)
```

The vectors are manually chosen for teaching. They are not learned by training.

## Bridge to Lesson 04: from independent token+position vectors to contextual vectors

After Lesson 03, the model input has shape:

```text
T x hidden_size
```

Each row contains:

- token identity;
- position information.

But each row is still mostly independent at construction time. The row for `dog` does not yet fully depend on `bites` or `man`.

Lesson 04 will look at a transformer block from the outside: how a matrix of token+position vectors becomes a matrix of contextual vectors. We will still avoid Q/K/V until the outside behavior is clear.

## Common confusions

### "Does adding position create a bigger vector?"

No. `E(token_i)` and `P(i)` have the same shape, so their sum also has shape `hidden_size`.

### "Does position alone explain sentence meaning?"

No. Position tells the model where tokens appear. Later layers are needed for tokens to influence each other.

### "Does the same token always have the same final input vector?"

No. The token embedding is the same, but the final input vector changes when the position changes.

### "Are these position vectors hand-designed?"

In this lab, yes, for teaching. In real learned absolute positional embeddings, they are learned parameters.

## Boundaries

This lesson intentionally stops before transformer internals:

- no attention internals;
- no Q/K/V;
- no KV cache internals;
- no RoPE math;
- no training loop.

## Session summary

### 1. Concepts learned

- Token embeddings encode token identity but not order.
- Positional information tells the model where each token appears.
- In the simplified absolute-position view, `P(i)` is a learned vector for position `i`.
- `X_i = E(token_i) + P(i)` combines token identity and position.
- The sequence shape remains `T x hidden_size`.
- The same token embedding can produce different final vectors at different positions.
- After Lesson 03, each row knows token identity and position, but not yet full context.

### 2. Open questions

- How do token+position vectors become contextual vectors?
- How do tokens start to depend on other tokens?
- What does a transformer block do from the outside?

### 3. Next concrete step

Read Lesson 04 next: Transformer block from the outside: how tokens become contextual.

### 4. Repo changes

- Polished `notes/03-positional-information.md` into a consistent chapter.
- Added a compact visual table for `token`, `token_id`, `E(token)`, `position`, `P(i)`, and `X_i`.
- Clarified why the shape remains `T x hidden_size`.
- Added a bridge to Lesson 04 without introducing Q/K/V.
