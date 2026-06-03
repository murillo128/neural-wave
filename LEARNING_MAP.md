# LEARNING_MAP

## Current milestone

Milestone 1: Understanding token-by-token inference.

## Active labs

- `labs/01-tokenizer-visualizer/`
- `labs/02-embedding-lookup/`

## Concepts covered

### 01 - Tokenization and next-token inference

- Text is transformed through `text -> tokens -> token IDs` before model inference.
- A tokenizer/model pair uses a fixed vocabulary.
- Token IDs are arbitrary integer indices into that vocabulary; nearby ID numbers are not necessarily semantically related.
- A tokenizer can be multilingual when its vocabulary and training data cover multiple languages, scripts, symbols, code, punctuation, and other domains.
- Tokenization efficiency varies by language and domain.
- More tokens for the same text use more context, add inference work, increase latency, and can raise product cost.
- The model predicts logits over the fixed vocabulary.
- Softmax converts logits into probabilities.
- High-level autoregressive loop: `token IDs -> logits -> probabilities -> next token ID -> append to context -> repeat`.

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
- Why words in different languages can end up close in embedding space.
- How magnitude and direction are both useful.
- Practical trade-off between larger vocabularies and fewer tokens.
- Quantization impact on embeddings/lm_head.

## Open questions

- How does a token ID become a vector?
- Why can embeddings encode semantic similarity?
- Why can words in different languages end up close in embedding space?
- What is the difference between prefill and decode in the autoregressive loop?
- Why does output vocabulary size affect the final projection and softmax cost?
- How does the model know the order of tokens?
- Why do "dog bites man" and "man bites dog" differ?
- How do embeddings become contextual?
- How do tokens interact with each other?
- What is positional information?
- Later, what exactly is stored in KV cache?
- Later, how does quantization affect quality?

## Next concrete step

Embeddings: token IDs -> learned vectors.

Goal:

- Understand why token ID numbers are not passed directly as meaningful numeric values.
- Learn embedding lookup: `x = E[token_id]`.
- Connect tokenization to the next stage of the inference pipeline.
