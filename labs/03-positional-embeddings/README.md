# Lab 03: Positional Embeddings

This lab demonstrates how positional information can be added to token embeddings before the first transformer block.

The key idea is:

```text
final input vector = token embedding + positional embedding
X_i = E(token_i) + P(i)
```

## Purpose

Lesson 02 showed that a token ID selects a token embedding. That tells the model what token is present, but not where the token appears.

This lab shows a simplified absolute positional embedding setup. Each position has a vector with the same dimensionality as the token embedding, so the two vectors can be added.

## What the executable shows

The program uses a tiny vocabulary:

```text
dog   -> 0
bites -> 1
man   -> 2
```

It compares two sentences:

```text
dog bites man
man bites dog
```

For each token, it prints:

- token;
- position;
- token embedding;
- position embedding;
- final input vector: `token embedding + position embedding`.

## Expected observation

The token embedding for `dog` is always the same:

```text
E("dog")
```

But the final vector changes depending on where `dog` appears:

```text
E("dog") + P(0) != E("dog") + P(2)
```

Therefore the model can distinguish `dog at position 0` from `dog at position 2`.

## Important limitation

This is not training. The token vectors and positional vectors are manually selected for teaching.

Real learned absolute positional embeddings are parameters updated during training because useful position vectors reduce prediction error.

## Boundary

This lab stops before attention. It only shows the construction of the vectors that would be passed onward after token identity and position have been combined.

## Build and run

From this directory:

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
./positional_embeddings
```
