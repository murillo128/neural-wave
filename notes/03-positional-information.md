# 03 - Positional Information: how does the model know order?

## Goal

Explain why token embeddings alone are not enough, and how positional information is added before entering the first transformer block.

After Lesson 02, we know that token IDs become vectors through an embedding lookup. That answers one important question:

```text
what token is this? -> token embedding
```

This lesson adds the next missing piece:

```text
where is this token? -> positional information
```

The boundary is important: this lesson stops before attention and before transformer block internals. We are only building the input vectors that will be handed to the first block.

## Conceptual explanation

Token embeddings answer:

```text
what token is this?
```

For example:

```text
E("dog")   -> vector for dog
E("bites") -> vector for bites
E("man")   -> vector for man
```

But token embeddings do not answer:

```text
where is this token in the sequence?
```

Consider these two sequences:

```text
dog bites man
man bites dog
```

They contain the same three token embeddings:

```text
E("dog")
E("bites")
E("man")
```

The difference is the order. In the first sentence, `dog` is at position `0` and `man` is at position `2`. In the second sentence, `man` is at position `0` and `dog` is at position `2`.

If we only perform token embedding lookup, the model has vectors for token identity, but it lacks an explicit signal for token location. The missing information is position/order.

So before the first transformer block receives the sequence, each token vector is enriched with position information.

## Minimal math

Define:

- `T`: sequence length, measured in tokens.
- `hidden_size` or `H`: number of numeric components in each vector.
- `X_tokens`: token embedding matrix after lookup.
- `P`: absolute positional embedding table.

After embedding lookup, a sequence has shape:

```text
X_tokens: T x hidden_size
```

For learned absolute positional embeddings, the position table has shape:

```text
P: max_context_size x hidden_size
```

Each row `P(i)` is the positional embedding for absolute position `i`.

For each token position:

```text
X_i = E(token_i) + P(i)
```

The final input matrix has shape:

```text
X: T x hidden_size
```

The shape does not change after adding position. This works because the positional vector has the same dimensionality as the token embedding:

```text
E(token_i): hidden_size
P(i):       hidden_size
-----------------------
X_i:        hidden_size
```

So if the sequence has `T` tokens, the result is still one `hidden_size` vector per token.

## Geometric intuition

Think of a token embedding as learned coordinates for token identity or meaning:

```text
E("dog") = coordinates for the token dog
```

Think of a positional embedding as a learned displacement associated with a position:

```text
P(0) = displacement for position 0
P(1) = displacement for position 1
P(2) = displacement for position 2
```

Then the final input vector is like:

```text
token identity coordinates + position displacement
```

For the same token at different positions:

```text
E("dog") + P(0)  -> dog at position 0
E("dog") + P(2)  -> dog at position 2
```

A simple picture:

```text
same token vector, different position displacements

E("dog") ---- + P(0) ----> representation of dog at position 0
E("dog") ---- + P(2) ----> representation of dog at position 2
```

This means `dog at position 0` and `dog at position 2` are represented differently.

Important caution: the final vector is not a human-readable tuple like:

```text
(token = dog, position = 2)
```

It is still just a vector. The token and position information are combined into coordinates useful to the model.

## How are P(0), P(1), P(2), ... calculated?

In learned absolute positional embeddings, `P(0)`, `P(1)`, `P(2)`, and so on are rows in a learned table, similar to token embeddings.

The analogy is:

```text
Token embeddings:
    dog -> vector
    cat -> vector

Position embeddings:
    0 -> vector
    1 -> vector
    2 -> vector
```

At initialization, the position vectors usually start as random or small random values, like other learned weights.

During training, the optimizer updates them because better position vectors help reduce prediction error. If a certain way of representing `position 0`, `position 1`, or `position 2` helps the model predict text better, training can move those vectors in useful directions.

They are not hand-coded meanings like:

```text
P(0) = "first"
P(1) = "second"
P(2) = "third"
```

They are learned statistical coordinates.

## What happens when text exceeds the context window?

In this simplified absolute-position view, the model has a finite table of position vectors.

For example, if:

```text
context_window = 4096
```

then learned absolute positional embeddings are available for:

```text
P(0), P(1), ..., P(4095)
```

But:

```text
P(4096)
P(4097)
...
```

may not exist.

Common outcomes when input is too long include:

- the model or API rejects the input as too long;
- the application truncates the input;
- the application chunks, summarizes, or retrieves selected parts of the input;
- experimental extension or interpolation is attempted, but it is not guaranteed to work.

The deeper limitation is that learned absolute positional embeddings are independent rows. Nothing guarantees that `P(1000)` and `P(1001)` have a smooth or extrapolatable relationship.

This motivates later techniques such as RoPE. For now, only the concept matters: RoPE encodes position through a mathematical rule/geometric transformation rather than simply learning one independent vector per absolute position. The RoPE mathematics is a later topic.

## Implementation summary

The lab in `labs/03-positional-embeddings/` demonstrates positional embedding addition with a tiny C++ program.

It uses:

- tiny vocabulary: `dog`, `bites`, `man`;
- fixed token IDs;
- `hidden_size = 4`;
- manually chosen token embeddings;
- manually chosen positional embeddings;
- two sentences:
  - `dog bites man`
  - `man bites dog`

For each token, the lab prints:

- token;
- position;
- token embedding;
- positional embedding;
- final vector: `token embedding + positional embedding`.

The key observation is:

```text
E("dog") is the same in both sentences
```

but:

```text
E("dog") + P(0) != E("dog") + P(2)
```

The lab vectors are manually chosen for teaching. They are not learned by training.

## Practical impact

Positional information is needed before the first transformer block.

The first transformer block receives vectors that already contain both:

```text
token identity + position
```

Absolute positional embeddings are easy to understand because they are just another learned table. Their parameter count is:

```text
max_context_size * hidden_size
```

But they have long-context limitations. They do not naturally extrapolate beyond the context length they were designed or trained for.

Modern models often use alternatives such as RoPE, but those details are for later lessons.

## Boundaries

This lesson intentionally does not cover:

- attention;
- Q/K/V;
- transformer block internals;
- KV cache;
- quantization;
- full training loop;
- RoPE mathematics.

## Session summary

### 1. Concepts learned

- Embeddings encode token identity but not order.
- A sequence after embedding lookup has shape `T x hidden_size`.
- Positional embeddings can be added to token embeddings.
- `X_i = E(token_i) + P(i)`.
- The final shape remains `T x hidden_size`.
- Learned absolute positional embeddings are trained parameters.
- The same token gets a different final vector at different positions.
- Absolute positional embeddings have trouble extrapolating beyond the context length they were designed/trained for.
- RoPE is a later conceptual motivation, not explained here.

### 2. Open questions

- How does the model use this positional information?
- How do tokens interact after receiving token + position vectors?
- How does attention mix information between tokens?
- Why do many modern models use RoPE or similar techniques?
- What exactly enters and exits a transformer block?

### 3. Next concrete step

Lesson 04:
"Transformer block from the outside: how tokens become contextual"
or similar.

Do not enter Q/K/V yet. The next lesson should explain at a high level that tokens start as independent `meaning + position` vectors and later become contextualized through block processing.

### 4. Repo changes

- Added `notes/03-positional-information.md`.
- Added `labs/03-positional-embeddings/`.
- Updated `README.md`.
- Updated `LEARNING_MAP.md`.
- Updated `GLOSSARY.md`.
- Updated `QUESTIONS.md`.
