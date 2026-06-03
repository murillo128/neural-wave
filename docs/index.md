# Neural Wave

A lightweight LLM learning book with small C++ labs.

This project is designed to build deep intuition about language models without trying to master every layer before touching the next one.

## Learning approach

We learn in a spiral:

1. See the concept simply.
2. Build a tiny lab.
3. Return later with more mathematical depth.
4. Connect the concept to inference, training, serving, and product impact.

!!! note "Book + lab"
    The lessons are the book. The C++ labs are small executable experiments that make each idea concrete.

## Current milestone

Understanding token-by-token inference.

```text
text
  -> tokens
  -> token IDs
  -> embeddings
  -> token + position vectors
  -> transformer blocks
  -> logits
  -> probabilities
  -> next token
```

## Current chapters

- [01 - Tokenization](lessons/01-tokenization.md)
- [02 - Embeddings](lessons/02-embeddings.md)
- [03 - Positional Information](lessons/03-positional-information.md)

## Current labs

- [01 - Tokenizer Visualizer](labs/01-tokenizer-visualizer.md)
- [02 - Embedding Lookup](labs/02-embedding-lookup.md)
- [03 - Positional Embeddings](labs/03-positional-embeddings.md)

## Boundaries

We are not yet explaining attention internals, Q/K/V, KV cache internals, RoPE mathematics, training, fine-tuning, RAG, quantization, batching, or serving. Those topics come later.
