# LEARNING_MAP

## Current milestone

**Milestone 1: Understanding token-by-token inference.**

The repo is currently building the pipeline from text into the first model-ready vectors:

```text
text -> tokens -> token IDs -> embeddings -> token+position vectors
```

The next step is to understand, from the outside, how those vectors become contextual during transformer processing.

## Completed chapters

### 00 - How to read this repo

- The repo is a lightweight learning book plus runnable C++ labs.
- Lessons use a spiral approach: concept, minimal math, intuition, implementation model, practical impact, lab, summary.
- Labs are intentionally tiny, explicit, and educational rather than optimized.

### 01 - Tokenization

- LLMs do not consume raw text directly.
- Text is transformed through `text -> tokens -> token IDs` before model inference.
- A tokenizer/model pair uses a fixed vocabulary.
- Token IDs are arbitrary integer indices into that vocabulary; nearby ID numbers are not necessarily semantically related.
- A tokenizer can be multilingual when its vocabulary and training data cover multiple languages, scripts, symbols, code, punctuation, and other domains.
- Tokenization efficiency varies by language and domain.
- Unknown or rare text may be split into smaller pieces.
- More tokens for the same text use more context, add inference work, increase latency, and can raise product cost.
- High-level autoregressive loop: `text -> tokens -> token IDs -> embeddings -> transformer -> logits -> probabilities -> next token -> append -> repeat`.

Lab: `labs/01-tokenizer-visualizer/`

### 02 - Embeddings

- Token IDs are arbitrary indices.
- Embedding lookup maps token IDs to learned vectors.
- `embedding_table[vocab_size][hidden_size]`
- `x = E[token_id]`
- A sequence becomes a matrix `T x hidden_size`.
- Dot product and cosine similarity compare vectors in different ways.
- Embeddings are learned coordinates, not explicit definitions.
- Initial embeddings are non-contextual.
- Input embeddings select one row for each token ID.
- The output projection, or `lm_head`, scores every vocabulary item from a final hidden vector.
- Logits are raw token scores before softmax.
- Softmax converts logits into a probability distribution.
- Embeddings and `lm_head` scale with `vocab_size * hidden_size`.

Lab: `labs/02-embedding-lookup/`

### 03 - Positional Information

- Token embeddings encode token identity but not order.
- `dog bites man` and `man bites dog` contain the same token embeddings in a different order.
- A sequence after embedding lookup has shape `T x hidden_size`.
- Absolute positional embeddings use a table with shape `max_context_size x hidden_size`.
- Each input vector can be formed as `X_i = E(token_i) + P(i)`.
- The final input to the first transformer block still has shape `T x hidden_size`.
- Learned positional embeddings are trained parameters, initialized like other learned weights.
- The same token receives a different final vector at different positions.
- After Lesson 03, each row knows token identity and position, but not yet full context.
- RoPE is a later positional technique, only introduced conceptually for now.

Lab: `labs/03-positional-embeddings/`

## Current frontier

Lesson 04 remains:

**Transformer block from the outside: how tokens become contextual.**

Goal:

- Understand that the first transformer block receives `T x hidden_size` vectors already containing token identity + position.
- Understand at a high level that later blocks let token representations depend on other tokens.
- Understand the input/output shape of a block before studying internals.
- Do not introduce Q/K/V yet.

## Concepts partially understood

- Weight tying.
- Why related tokens become geometrically close.
- Why words in different languages can end up close in embedding space.
- How magnitude and direction are both useful.
- Practical trade-off between larger vocabularies and fewer tokens.
- Quantization impact on embeddings/lm_head as a memory and serving concern.

## Do not jump ahead yet

The following topics are intentionally postponed:

- attention internals;
- Q/K/V;
- KV cache internals;
- RoPE math;
- training loops;
- fine-tuning;
- RLHF or DPO;
- RAG implementation details;
- quantization internals.

These will be easier once the outside shape of token-by-token inference is clear.

## Next concrete step

Write Lesson 04 as a chapter about the transformer block from the outside:

```text
T x hidden_size token+position vectors
  -> transformer block
  -> T x hidden_size contextual vectors
```

The lesson should explain what changes conceptually while preserving the boundary that Q/K/V is not introduced yet.
