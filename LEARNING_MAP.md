# LEARNING_MAP

## Current milestone

Understand token-by-token inference and build a tokenizer visualizer.

## Active labs

- `labs/01-tokenizer-visualizer/`

## Concepts covered

- Why text is transformed into tokens before model inference.
- Basic mapping from tokens to token IDs.
- Fixed vocabulary used by a tokenizer/model pair.
- Token IDs as arbitrary integer indices with no numeric semantic distance.
- Multilingual tokenization with shared English, Spanish, code, punctuation, and symbol coverage.
- How tokenizer coverage changes token count and `[UNK]` behavior.
- How token count affects cost, context usage, latency, and serving throughput.
- Logits over the fixed vocabulary.
- Softmax at a high level.
- Autoregressive generation loop: previous token IDs -> next token ID -> append to context.

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

Embeddings: token IDs -> learned vectors.
