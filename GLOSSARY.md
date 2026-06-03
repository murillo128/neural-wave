# GLOSSARY

## Token

A unit of text consumed by a language model.

## Tokenizer

A component that converts text into tokens and token IDs.

## Detokenization

Converting token IDs or tokens back into text, when the tokenization scheme preserves enough information.

## Vocabulary

The fixed set of tokens known by a tokenizer/model pair.

## Vocab size

The number of tokens in the vocabulary.

## Token ID

An arbitrary integer index for a token in the vocabulary.

## Multilingual tokenizer

A tokenizer whose vocabulary covers text patterns from multiple languages, scripts, and domains.

## Embedding

A learned vector representation associated with a token ID.

## Embedding table

A learned matrix with shape `vocab_size x hidden_size`. Each row contains the embedding vector for one token.

## Embedding lookup

The operation of selecting an embedding table row by token ID: `x = E[token_id]`.

## `hidden_size`

The dimensionality of each token vector or hidden representation.

## Sequence length `T`

The number of tokens in a sequence.

## Dot product

A vector comparison computed as `a · b = sum(a_i * b_i)`.

## Norm

The length or magnitude of a vector, commonly written as `||a||`.

## Cosine similarity

A normalized vector similarity score: `(a · b) / (||a|| * ||b||)`, focused mostly on direction.

## `lm_head`

The output projection that maps a final hidden vector to logits over the vocabulary.

## Logit

A raw, unnormalized score for a possible next token before softmax.

## Softmax

A function that converts logits into probabilities that sum to 1.

## Sampling

Choosing a next token from the probability distribution instead of always taking the top token.

## Greedy decoding

Choosing the highest-probability next token at each generation step.

## Autoregressive generation

Generating one token at a time by conditioning on previous tokens and appending each selected token to the context.

## Weight tying

Sharing the same weights between the embedding table and the `lm_head` projection.

## Context window

Maximum number of tokens a model can process in a request.

## Prefill

Phase where the model processes the prompt tokens.

## Decode

Phase where tokens are generated one-by-one.

## KV cache

Stored key/value attention states used to speed generation.

## Quantization

Reducing numeric precision of weights/activations for efficiency.
