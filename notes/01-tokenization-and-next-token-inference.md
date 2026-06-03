# Tokenization and next-token inference

LLMs process token IDs, not raw text. Before text can be used by a model, it is converted through this pipeline:

```text
text -> tokens -> token IDs
```

A tokenizer splits text into tokens such as words, word pieces, punctuation, spaces, symbols, or code fragments. Each token is then looked up in a fixed vocabulary to produce an integer token ID.

## Fixed vocabulary and token IDs

The vocabulary is fixed for a trained model. It is the list of tokens the tokenizer knows how to map to IDs. If a token is not covered well by the vocabulary, the tokenizer may need to represent it with more pieces or fall back to a special token such as `[UNK]` in this educational lab.

Token IDs are arbitrary integer indices into the vocabulary. The numeric distance between two token IDs has no semantic meaning by itself. For example, token ID `10` is not necessarily more similar to token ID `11` than to token ID `5000`.

Semantic meaning starts when token IDs are used to look up learned vectors in an embedding table. Embeddings are the next learning step.

## Multilingual tokenization

One shared vocabulary can contain tokens for English, Spanish, code, punctuation, whitespace, symbols, and many other text patterns. A multilingual tokenizer does not need a separate vocabulary for every language, but its efficiency depends on tokenizer coverage.

Good coverage means common words or word pieces can be represented with fewer tokens. Poor coverage means text may become many small tokens, or in a simple educational tokenizer, may become `[UNK]`. This is why the same number of characters can produce different token counts across languages or domains.

## Autoregressive next-token inference

After tokenization, a high-level autoregressive generation loop looks like this:

```text
previous token IDs -> logits -> softmax -> next token ID -> append to context
```

At each step, the model estimates:

```text
P(next_token | previous_tokens)
```

The model outputs one logit for each token in the fixed vocabulary. A logit is an unnormalized score. Softmax turns those scores into probabilities:

```text
p_i = exp(logit_i) / sum_j exp(logit_j)
```

A decoding rule then chooses the next token ID. Greedy decoding chooses the highest-probability token. Sampling chooses from the probability distribution. The selected token ID is appended to the context, and the loop repeats.

## Practical impact of token count

Token count affects:

- Context usage: prompts and generated answers must fit inside the context window.
- Latency: more tokens usually mean more computation.
- Cost: many providers bill by input and output tokens.
- Serving throughput: fewer tokens can allow more requests or generations with the same compute budget.

## Concepts learned

- LLM input is token IDs, not raw text.
- Tokenization maps `text -> tokens -> token IDs`.
- A model uses a fixed vocabulary.
- Token IDs are arbitrary indices, not semantic numbers.
- Multilingual and code text can share one vocabulary.
- Tokenizer coverage affects token count and `[UNK]` behavior.
- Next-token inference produces logits over the vocabulary.
- Softmax converts logits into probabilities.
- Autoregressive generation appends each selected next token ID to the context.

## Open questions

- How does a token ID become a vector?
- Why can learned vectors encode semantic similarity?
- How can related meanings across languages end up near each other?
- Why does vocab size affect the cost of the final projection and softmax?

## Next step

Embeddings: token IDs -> learned vectors.
