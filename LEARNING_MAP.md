# LEARNING_MAP

## Current milestone

Milestone 1: Understanding token-by-token inference.

## Active labs

- `labs/01-tokenizer-visualizer/`
- `labs/02-embedding-lookup/`
- `labs/03-positional-embeddings/`

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

### 03 - Positional Information

- Token embeddings encode token identity but not order.
- `dog bites man` and `man bites dog` contain the same token embeddings in a different order.
- A sequence after embedding lookup has shape `T x hidden_size`.
- Absolute positional embeddings use a table with shape `max_context_size x hidden_size`.
- Each input vector can be formed as `X_i = E(token_i) + P(i)`.
- The final input to the first transformer block still has shape `T x hidden_size`.
- Learned positional embeddings are trained parameters, initialized like other learned weights.
- The same token receives a different final vector at different positions.
- Absolute positional embeddings have long-context extrapolation limitations.
- RoPE is a later positional technique, only introduced conceptually for now.

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
- How do embeddings become contextual?
- How do tokens interact with each other?
- What exactly is stored in KV cache?
- How does attention use position?
- Why does RoPE help long-context models?
- Later, how does quantization affect quality?

## Recently answered

- How does the model know the order of tokens?
- Why do "dog bites man" and "man bites dog" differ?
- What is positional information?

## Next concrete step

Lesson 04: Transformer block from the outside: how tokens become contextual.

Goal:

- Understand that the first transformer block receives `T x hidden_size` vectors already containing token identity + position.
- Understand at a high level that later blocks let token representations depend on other tokens.
- Do not introduce Q/K/V yet.
