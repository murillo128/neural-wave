# GLOSSARY

## Token

A unit of text consumed by a language model.

## Subword token

A token that represents part of a word or text pattern rather than a complete word.

## Byte-level tokenizer

A tokenizer that can fall back to byte-like pieces so unusual text can still be represented.

## Unknown token

A special token used by some tokenizers when text cannot be represented by known vocabulary pieces.

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

## Context usage

The amount of a model's context window consumed by a tokenized input and generated output.

## Context window

Maximum number of tokens a model can process in a request.

## Next-token prediction

The task of scoring possible next tokens given the tokens already in the context.

## Embedding

A learned vector representation associated with a token ID.

## Non-contextual embedding

The initial token vector selected by token ID before later layers let it depend on surrounding tokens.

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

## Output projection

The vocabulary-sized projection that maps a final hidden vector to one score per possible next token.

## `lm_head`

The output projection that maps a final hidden vector to logits over the vocabulary.

## Logit

A raw, unnormalized score for a possible next token before softmax.

## Probability distribution

A set of probabilities over choices, such as vocabulary tokens, that sum to 1.

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

## Positional information

Information that tells the model where a token appears in a sequence.

## Positional embedding

A vector associated with a token position, with the same dimensionality as token embeddings.

## Absolute positional embedding

A positional embedding scheme where each absolute position has its own learned vector, commonly represented as `P(i)`.

## Position embedding table

A learned matrix with shape `max_context_size x hidden_size`.

## `max_context_size`

The maximum number of token positions for which a model has positional information in this simplified absolute-position view.

## `X_i = E(token_i) + P(i)`

The simplified input construction where a token embedding and its positional embedding are added to produce the vector passed onward.

## Contextual representation

A token vector after later model layers have allowed it to depend on other tokens in the sequence.

## Chapter boundary

A deliberate stopping point that says which ideas are in scope now and which are postponed.

## RoPE

A modern positional technique that encodes position using a geometric/mathematical transformation. In this repo it is only introduced conceptually for now; the math comes later.

## Prefill

Phase where the model processes the prompt tokens.

## Decode

Phase where tokens are generated one-by-one.

## KV cache

Stored attention-related state used to speed generation. Internals are postponed.

## Quantization

Reducing numeric precision of weights/activations for efficiency. Internals are postponed.
