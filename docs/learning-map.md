# Learning Map

## Current milestone

**Understanding token-by-token inference.**

The repo is currently building the pipeline from text into model-ready token vectors.

```text
text
  -> tokens
  -> token IDs
  -> embedding lookup
  -> T x hidden_size matrix
  -> add positional information
  -> still T x hidden_size
```

---

## Completed chapters

1. [01 - Tokenization](lessons/01-tokenization.md)
2. [02 - Embeddings](lessons/02-embeddings.md)
3. [03 - Positional Information](lessons/03-positional-information.md)

## Current frontier

[04 - Transformer Block from the Outside](lessons/04-transformer-block-from-the-outside.md)

This is the next lesson and should remain an outside-view stub until the first three chapters are solid.

---

## What we know so far

We know how to convert human text into token IDs, map token IDs to vectors, and add positional information while keeping the same sequence matrix shape.

## What we do not know yet

- how tokens interact;
- how representations become contextual;
- what attention does;
- Q/K/V;
- KV cache;
- prefill/decode details.

---

## Do not jump ahead yet

- no Q/K/V in Lesson 04;
- no RoPE math yet;
- no quantization internals yet.

Future topics can be mentioned as motivation, but they should not be explained before the learning path reaches them.

## Open questions

- How does an initial token+position vector become contextual?
- What enters and exits a transformer block?
- How can one token representation depend on another token?
