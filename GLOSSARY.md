# GLOSSARY

## Token
A unit of text consumed by a language model.

## Token ID
An integer representing a token in a vocabulary.

## Vocabulary
The fixed set of tokens a tokenizer and model can use.

## Vocab size
The number of tokens in the vocabulary.

## Context window
Maximum number of tokens a model can process in a request.

## Logit
A raw model score for a possible next token before probability conversion.

## Softmax
A function that converts logits into probabilities that sum to 1.

## Sampling
Choosing the next token from the probability distribution, often with controlled randomness.

## Greedy decoding
Always choosing the token with the highest probability.

## Autoregressive generation
Generating one token at a time, appending each selected token back into the context.

## Embedding
A learned vector representation looked up from a token ID.

## Detokenization
Converting token IDs or tokens back into text when the tokenizer is reversible enough.

## Multilingual tokenizer
A tokenizer whose vocabulary can represent text from multiple languages or scripts.

## Prefill
Phase where the model processes the prompt tokens.

## Decode
Phase where tokens are generated one-by-one.

## KV cache
Stored key/value attention states used to speed generation.

## Quantization
Reducing numeric precision of weights/activations for efficiency.
