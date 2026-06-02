# LEARNING_MAP

## Current milestone

Understand token-by-token inference and build a tokenizer visualizer.

## Active labs

- `labs/01-tokenizer-visualizer/`

## Concepts covered

- Text is transformed through `text -> tokens -> token IDs` before model inference.
- Token IDs are arbitrary integer indices into a fixed vocabulary.
- The tokenizer can be multilingual when its vocabulary and training data cover multiple languages.
- Token count affects context usage, latency, throughput, and cost.
- High-level autoregressive loop: `token IDs -> logits -> probabilities -> next token ID`.

## Concepts partially understood

- Practical differences between simple splitting and BPE-style merges.
- Why tokenization efficiency varies across languages and domains.
- How logits become probabilities during next-token generation.

## Open questions

- How does a token ID become a vector?
- What exactly is stored in KV cache?
- Why is decode slower than prefill?
- How does quantization affect quality?
- Why do providers differ if models are similar?

## Next concrete step

Embeddings: token IDs -> vectors.
