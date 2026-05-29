# LEARNING_MAP

## Current milestone

Understand token-by-token inference and build a tokenizer visualizer.

## Active labs

- `labs/01-tokenizer-visualizer/`

## Concepts covered

- Why text is transformed into tokens before model inference.
- Basic mapping from tokens to token IDs.
- How token count affects context usage and cost.

## Concepts partially understood

- Practical differences between simple splitting and BPE-style merges.
- Relationship between token count and throughput.
- How multilingual text impacts tokenization behavior.

## Open questions

- What exactly is stored in KV cache?
- Why is decode slower than prefill?
- How does quantization affect quality?
- Why do providers differ if models are similar?

## Next concrete step

Build and run `labs/01-tokenizer-visualizer`, then compare tokenization behavior for English, Spanish, and code examples.
