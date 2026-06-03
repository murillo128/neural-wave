# Glossary

## Token

A piece of text produced by a tokenizer. A token can be a word, subword, punctuation mark, whitespace-attached piece, byte-like piece, emoji, or symbol.

## Tokenizer

The component that converts text into tokens and token IDs using a fixed vocabulary.

## Detokenization

The reverse process of turning tokens or token IDs back into text-like output.

## Vocabulary

The fixed set of tokens known by a tokenizer/model pair.

## Vocab size

The number of entries in the vocabulary.

## Token ID

An arbitrary integer index for a vocabulary entry. Token IDs are not semantic magnitudes.

## Subword token

A token that represents part of a word or text fragment rather than a whole word.

## Byte-level tokenizer

A tokenizer family that can represent text through byte-level pieces. Production details are a later topic.

## Unknown token

A fallback token used by some tokenizers when text cannot be represented directly. Many modern tokenizers avoid a single unknown token by splitting text into smaller pieces.

## Context window

The maximum number of tokens a model/application can consider in one context.

## Context usage

The fraction of the context window consumed by a sequence, approximately \(usage = T / context\_window\).

## Next-token prediction

The task of predicting the next token from previous tokens.

## Embedding

A vector representation associated with a token ID.

## Embedding table

A learned matrix with shape \(vocab\_size \times hidden\_size\). Each row contains one token embedding.

## Embedding lookup

Selecting an embedding table row by token ID: \(x = E[token\_id]\).

## Hidden size

The dimensionality, or width, of each token vector or hidden representation.

## Sequence length \(T\)

The number of tokens in a sequence.

## Dot product

A vector comparison computed as \(a \cdot b = \sum_i a_i b_i\).

## Norm

The length or magnitude of a vector: \(\|a\| = \sqrt{\sum_i a_i^2}\).

## Cosine similarity

A normalized vector similarity score:

\[
\mathrm{cos}(a,b) = \frac{a \cdot b}{\|a\|\|b\|}
\]

## Non-contextual embedding

The initial token vector selected by token ID before later layers let it depend on surrounding tokens.

## Contextual representation

A token vector after later model layers have allowed it to depend on other tokens in the sequence.

## Positional information

Information that tells the model where a token appears in a sequence.

## Positional embedding

A vector associated with a token position, with the same dimensionality as token embeddings.

## Absolute positional embedding

A positional embedding scheme where each absolute position has its own learned vector.

## Position embedding table

A learned matrix with shape \(max\_context\_size \times hidden\_size\).

## \(X_i = E(token_i) + P(i)\)

The simplified construction where a token embedding and positional embedding are added to produce the vector passed onward.

## `lm_head`

The output projection that maps a final hidden vector to logits over the vocabulary.

## Output projection

The vocabulary-sized projection that produces one score for each possible next token.

## Logit

A raw, unnormalized score for a possible next token before softmax.

## Probability distribution

A set of probabilities over choices, such as vocabulary tokens, that sum to 1.

## Softmax

A function that converts logits into probabilities:

\[
p_i = \frac{e^{logit_i}}{\sum_j e^{logit_j}}
\]

## Sampling

Choosing a next token from the probability distribution instead of always choosing the top token.

## Greedy decoding

Choosing the highest-probability next token at each generation step.

## Weight tying

Sharing weights between the embedding table and the output projection. Details come later.

## Chapter boundary

A deliberate stopping point that says which ideas are in scope now and which are postponed.

## RoPE

Future topic. A modern positional scheme used by many LLMs. RoPE mathematics is not covered yet.

## KV cache

Future topic. Stored attention-related state used to speed generation. Internals are postponed.

## Quantization

Future topic. Lower-precision representation for efficiency. Internals are postponed.
