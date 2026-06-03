# Tokenization and next-token inference

## Conceptual explanation

The model does not read raw text directly. Before an LLM can work with a sentence, a tokenizer converts the text into tokens and then into token IDs.

The vocabulary is fixed for a tokenizer/model pair. Each token ID is an integer index into that vocabulary. The model predicts the next token ID from previous token IDs; it cannot invent a new token ID during inference.

At a high level, one generation step looks like this:

1. Previous token IDs are fed into the model.
2. The model outputs logits over the whole vocabulary.
3. Softmax converts those logits into probabilities.
4. Sampling or greedy decoding chooses one next token ID.
5. The chosen token ID is appended to the context.
6. The loop repeats.

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

For now, embeddings and the transformer are boxes in the middle of the pipeline. We know they are important, but we will study them later.

## Minimal math

The model is trying to estimate:

```text
P(next_token | previous_tokens)
```

For a sequence, the probability can be viewed as a chain of next-token predictions:

```text
P(t1, ..., tn)
=
P(t1) * P(t2 | t1) * P(t3 | t1, t2) * ...
```

Softmax turns one logit per vocabulary item into probabilities:

```text
p_i = exp(logit_i) / sum_j exp(logit_j)
```

Real implementations use a numerically stable variant of softmax so large logits do not cause overflow.

## Token IDs

`token_id = 1542` is just an index.

That means:

- `1542` and `1543` are not necessarily related.
- Similarity does not live in the ID number.
- Meaning is not in the integer.
- Meaning is learned later in embeddings and model weights.

This is why passing raw ID numbers as meaningful numeric features would be wrong. The ID only says which row to look up in a learned embedding table.

## Multilingual tokenization

A tokenizer can use one shared vocabulary for multiple languages and domains. English, Spanish, code, emojis, URLs, punctuation, and other scripts can coexist in the same vocabulary.

Coverage depends on the tokenizer training data. If the vocabulary covers a language or domain well, common text can be represented with fewer tokens. If coverage is poor, the same text may require more tokens or may fall back to unknown/smaller pieces in an educational tokenizer.

Examples to compare:

```text
"El gato está en la casa."
"The cat is in the house."
"std::vector<int>"
"superhipermegagato"
```

A rare or invented word like `superhipermegagato` can still be represented if the tokenizer can split it into smaller pieces. If it cannot, this lab may show `[UNK]` because it is intentionally simple.

More tokens for the same text means more cost and less effective context capacity.

## Practical impact

Tokenization affects real systems in several ways:

- Product cost: many hosted APIs charge by input and output token counts.
- Context window usage: more tokens leave less room for the rest of the prompt or answer.
- Latency: more tokens usually mean more inference work.
- Serving throughput: fewer tokens can let the same hardware serve more requests.
- Multilingual quality: poor vocabulary coverage can make some languages less efficient to process.
- Output projection / softmax cost: the model scores every vocabulary item when producing logits, so vocabulary size affects the final projection and probability step.

## What we know now

- LLMs operate on token IDs.
- Tokenizers define the discrete alphabet.
- Token IDs index the vocabulary.
- Token IDs are arbitrary indices, not semantic numbers.
- The tokenizer does not understand language.
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
