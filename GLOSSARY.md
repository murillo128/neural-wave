# GLOSSARY

## Token
A unit of text consumed by a language model.

## Token ID
An integer representing a token in a vocabulary.

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

## Tokenizer
A component that converts text into tokens and token IDs.

## Detokenizer
A component that converts token IDs or tokens back into text.

## Vocabulary
The fixed set of tokens known by a tokenizer/model pair.

## Vocab size
The number of tokens in the vocabulary.

## Logit
An unnormalized score for a possible next token.

## Softmax
A function that converts logits into probabilities that sum to 1.

## Sampling
Choosing a next token from the probability distribution.

## Greedy decoding
Choosing the highest-probability next token at each step.

## Autoregressive generation
Generating one token at a time by appending each selected token to the context.

## Embedding
A learned vector representation for a token ID.

## Embedding table
A learned lookup table that maps token IDs to embedding vectors.
