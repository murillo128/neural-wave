# Lab 03 - Positional Embeddings

## Location

`labs/03-positional-embeddings/`

## Lesson link

Read [Lesson 03 - Positional Information](../lessons/03-positional-information.md) first.

## What it demonstrates

- token embedding + positional embedding;
- same token at different positions has a different final vector;
- `dog bites man` vs `man bites dog`;
- final input vector before attention.

## Build and run

From the lab directory:

```bash
cmake -S . -B build
cmake --build build
./build/positional_embeddings
```

## What to observe

Compare `dog` in both sentences. The token embedding for `dog` stays the same, but the final vector changes because the positional embedding changes.

## What it is not

- no attention;
- no Q/K/V;
- no RoPE;
- no training.
