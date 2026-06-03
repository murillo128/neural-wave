# LEARNING_MAP

## Current milestone

Milestone 1: Understanding token-by-token inference.

## Active labs

- `labs/01-tokenizer-visualizer/`
- `labs/02-embedding-lookup/`

## Concepts covered

### 01 - Tokenization

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

### 02 - Embeddings

- Token IDs are arbitrary indices.
- Embedding lookup maps token IDs to learned vectors.
- `embedding_table[vocab_size][hidden_size]`
- `x = E[token_id]`
- A sequence becomes a matrix `T x hidden_size`.
- Dot product and cosine similarity.
- Embeddings as learned coordinates.
- `lm_head` maps final hidden vectors to logits.
- Logits are raw token scores before softmax.
- Embeddings/lm_head scale with `vocab_size * hidden_size`.

## Concepts partially understood

- Weight tying.
- Why related tokens become geometrically close.
- How magnitude and direction are both useful.
- Quantization impact on embeddings/lm_head.
- Practical trade-off between larger vocabularies and fewer tokens.

## Open questions

- How does the model know the order of tokens?
- Why do "dog bites man" and "man bites dog" differ?
- How do embeddings become contextual?
- How do tokens interact with each other?
- What is positional information?
- Later, what exactly is stored in KV cache?
- Later, why is decode slower than prefill?
- Later, how does quantization affect quality?

## Next concrete step

Study Lesson 03: Positional Information.

Goal:

- Understand why token embeddings alone are not enough.
- Introduce positional embeddings conceptually.
- Prepare for the first transformer block overview.
