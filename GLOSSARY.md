# GLOSSARY

## Token

A unit of text consumed by a language model.

## Vocabulary

The set of tokens a model can represent, each mapped to a token ID.

## Token ID

An arbitrary integer representing a token in a vocabulary.

## Embedding

A learned vector representation associated with a token ID.

## Embedding table

A learned matrix with shape `vocab_size x hidden_size`. Each row contains the embedding vector for one token.

## Embedding lookup

The operation of selecting an embedding table row by token ID: `x = E[token_id]`.

## `vocab_size`

The number of tokens in the vocabulary.

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

## Logits

Raw, unnormalized scores for each possible next token before softmax.

## Softmax

A function that converts logits into probabilities that sum to 1.

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
