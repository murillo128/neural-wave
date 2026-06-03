# Next session prompt — Positional Information

We have completed tokenization and embeddings.

Next lesson: Positional Information.

Do not enter attention, Q/K/V, or KV cache yet. Keep the lesson focused on why token embeddings alone are not enough to represent order.

Explain:

- why embeddings do not encode order by themselves
- why "dog bites man" and "man bites dog" differ even though they contain the same tokens
- the conceptual formula `X_i = E(token_i) + P(i)`
- positional embeddings / positional information conceptually
- a small C++ lab under `labs/03-positional-embeddings/`

End the session with:

1. Concepts learned.
2. Open questions.
3. Next concrete step.
4. Repo changes.
