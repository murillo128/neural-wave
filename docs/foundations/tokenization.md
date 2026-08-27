# Tokenization

Tokenization is the boundary between human text and the discrete symbols consumed by a language model.

## Mental model

A model does not receive a string such as `"Hello, world"` directly. The tokenizer first converts it into a sequence of vocabulary entries and then into integer IDs:

```text
text
  -> tokenizer
  -> tokens
  -> token IDs
  -> model
```

Formally, for a sequence of length \(T\):

\[
text \rightarrow (t_0,t_1,\ldots,t_{T-1})
     \rightarrow (id_0,id_1,\ldots,id_{T-1})
\]

The exact token boundaries depend on the tokenizer. Tokens are not the same thing as words.

## The tokenizer/model contract

A tokenizer and model must agree on the same vocabulary and special-token conventions.

If token ID `42` is emitted, the model interprets that integer as row `42` of its embedding table. Substituting a tokenizer with a different vocabulary does not merely change preprocessing: the IDs would point to the wrong learned vectors.

This is the first important distinction:

> A token ID is an **index**, not a numeric feature.

ID `100` is not ten times more meaningful than ID `10`, and adjacent IDs do not imply related meanings.

## Tokens are a compression/representation choice

A useful vocabulary must balance competing goals.

If the vocabulary contained only characters or bytes, arbitrary text would be easy to represent but sequences would be long. If it contained every possible word or phrase, the vocabulary would become enormous and still fail on unseen strings.

Subword tokenization occupies the middle ground: common fragments can be represented by larger pieces while unusual text falls back to smaller pieces.

For example, one tokenizer might encode:

```text
"unbelievable" -> ["un", "believ", "able"]
```

while another might use one token or many smaller pieces. Neither segmentation is inherently "correct" linguistically; the useful question is whether the resulting vocabulary and sequence lengths support efficient learning.

## BPE intuition

Byte Pair Encoding and BPE-like tokenizers are easiest to understand as a learned compression dictionary.

During tokenizer construction, a corpus is represented with small initial symbols. The algorithm repeatedly finds frequent adjacent pairs and promotes useful combinations into larger vocabulary pieces. The learned vocabulary/merge rules are then fixed and used to encode future text.

A simplified picture is:

```text
initial pieces:   l o w e r
frequent merges:  l+o -> lo
                  lo+w -> low
                  e+r -> er
resulting pieces: low er
```

Production tokenizers differ in details, but the important idea is that common local patterns earn compact representations.

Many modern BPE-family tokenizers operate over bytes or include byte fallback. That provides coverage for arbitrary Unicode text without requiring a single `unknown` token for every unseen character sequence.

## Unigram tokenization is a different idea

Unigram/SentencePiece-style tokenization should not be mentally reduced to BPE.

Instead of building one ordered list of pair merges, a unigram model maintains candidate pieces with learned scores and chooses a good segmentation of the whole string. Several segmentations may be possible; the tokenizer chooses the one favored by its model.

Both approaches produce subword vocabularies, but the construction and segmentation logic differ.

## Tokenization is normally fixed before model training

The tokenizer vocabulary is usually constructed before large-scale model pretraining and then kept fixed while the neural-network weights learn.

This creates a durable interface:

```text
text distribution
      |
      v
fixed tokenizer/vocabulary
      |
      v
IDs -> learned embedding table -> transformer
```

The neural model can become far more sophisticated, but it is still constrained to see text through the discrete units chosen by the tokenizer.

## Why languages and code tokenize differently

Vocabulary pieces reflect the corpus and construction algorithm used to build the tokenizer. Text patterns that received useful dedicated pieces can be represented compactly; less well-covered patterns may fragment into more tokens.

That is why token counts can vary substantially across:

- languages;
- source code;
- whitespace conventions;
- punctuation;
- accented characters;
- identifiers and hashes;
- mathematical notation;
- emojis and uncommon Unicode sequences.

The effect is not evidence that the tokenizer "understands" one language better. It is a property of the discrete representation it learned.

## Context is counted in tokens

If a sequence contains \(T\) tokens and the usable context is \(C\) tokens, a simple occupancy ratio is

\[
\frac{T}{C}.
\]

The token count matters because the transformer operates over token positions. During prompt processing, longer sequences mean more positions to represent and more attention work. During generation, every new output token extends the autoregressive sequence.

The exact latency and memory consequences depend on architecture and inference implementation, so "twice as many tokens" does not imply one universal cost multiplier. But tokens are the fundamental sequence-length unit.

## Connection to embeddings

Tokenization produces discrete IDs, but those integer values contain no useful geometry by themselves. The next learned interface is an embedding table:

\[
id_i \longrightarrow E[id_i] \in \mathbb{R}^{d}.
\]

That step moves the computation from arbitrary symbols into a continuous vector space. See [Embeddings and Representation Geometry](embeddings-and-representation-geometry.md).

## Practical consequences

Tokenization affects product and infrastructure decisions because it changes effective sequence length: context capacity, prompt cost, prefill work, retrieval chunk boundaries, and how much output can be generated within a limit.

Those consequences are useful context, but the conceptual point is simpler: **the tokenizer defines the discrete language in which the neural model receives and emits text**.
