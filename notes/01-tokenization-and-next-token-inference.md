# Tokenization and next-token inference

## Conceptual explanation

The model does not read raw text directly. Before text reaches the model, a tokenizer converts it into tokens, then into token IDs. Those IDs are integer indices into a fixed vocabulary.

The IDs are not meaningful by themselves. A token ID like `1542` is just an index. The model learns what to do with that index later through embeddings and transformer weights.

At a high level, next-token inference looks like this:

```text
text
  -> tokens
  -> token IDs
  -> embeddings
  -> transformer
  -> logits
  -> probabilities
  -> next token ID
  -> text
```

This note focuses on tokenization and the next-token loop. Embeddings and the transformer will be studied later.

Once the prompt has become token IDs, the model predicts the next token ID from the previous token IDs. It outputs logits over the whole vocabulary. Softmax converts those logits into probabilities. Then either sampling or greedy decoding chooses one token. The chosen token ID is appended to the context, and the loop repeats.

## Minimal math

The model is trying to estimate:

```text
P(next_token | previous_tokens)
```

A full sequence probability can be broken into next-token probabilities:

```text
P(t1, ..., tn)
=
P(t1) * P(t2 | t1) * P(t3 | t1, t2) * ...
```

Softmax turns one logit per vocabulary item into one probability per vocabulary item:

```text
p_i = exp(logit_i) / sum_j exp(logit_j)
```

Real implementations use a numerically stable variant so the exponentials do not overflow.

## Token IDs

`token_id = 1542` is just an index into the vocabulary.

That means:

- `1542` and `1543` are not necessarily related.
- Similarity does not live in the ID number.
- Meaning is not in the integer.
- Meaning is learned in embeddings and model weights.

The tokenizer defines the discrete alphabet the model can use. During inference, the model cannot invent a brand-new token ID outside that fixed vocabulary. New or rare words can still be represented if the tokenizer can split them into smaller known pieces.

## Multilingual tokenization

A tokenizer can use one shared vocabulary for multiple languages. English, Spanish, code, emojis, URLs, punctuation, and other scripts can coexist in the same vocabulary.

Coverage depends on the tokenizer training data. If the vocabulary has poor coverage for a language or domain, the same text may become more tokens. More tokens means more cost, more context usage, more inference work, and less effective context capacity.

Examples to compare:

```text
"El gato está en la casa."
"The cat is in the house."
"std::vector<int>"
"superhipermegagato"
```

A strong multilingual tokenizer may represent common words or subwords efficiently across languages. A weaker tokenizer may split accented text, code punctuation, or rare compound words into many small pieces.

## Practical impact

Tokenization affects product and serving behavior:

- Product cost: more tokens can mean more billable input and output work.
- Context window usage: more tokens consume the available context faster.
- Latency: more tokens require more model steps and computation.
- Serving throughput: extra token work reduces how many requests a system can serve.
- Multilingual quality: poor coverage can make non-English text less efficient and harder for the model to handle well.
- Output projection / softmax cost: the model scores the fixed vocabulary when predicting the next token, so vocabulary size affects the final projection and probability calculation.

## What we know now

- LLMs operate on token IDs.
- Tokenizers define the discrete alphabet.
- Token IDs index the vocabulary.
- The model predicts logits over the vocabulary.
- Generation is a loop.
- Tokenizer efficiency matters.

## Open questions

- How do embeddings turn IDs into vectors?
- Why does vector geometry capture meaning?
- How does attention use those vectors?
- What exactly is cached in KV cache?
- Why is decode different from prefill?

## Next step

Embeddings: token IDs -> learned vectors.
