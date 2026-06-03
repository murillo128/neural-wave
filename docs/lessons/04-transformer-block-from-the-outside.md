# 04 - Transformer Block from the Outside

!!! warning "Status"
    Draft / upcoming lesson.

## Goal

Understand how token+position vectors start becoming contextual representations.

## What we already know

- Tokenization converts text to token IDs.
- Embeddings convert token IDs to vectors.
- Positional information adds order.
- The input to the first transformer block has shape \(T \times hidden\_size\).

## What this lesson will explain

- A transformer block as a vector-to-vector processor.
- Input shape: \(T \times hidden\_size\).
- Output shape: \(T \times hidden\_size\).
- Each output vector can depend on other tokens.
- The difference between non-contextual input vectors and contextual representations.

## Out of scope

- Q/K/V.
- Attention math.
- KV cache.
- RoPE math.
- Training.
