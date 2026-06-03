# 01 - Tokenization

## Goal

Understand that LLMs do not consume raw text directly. Text is converted to tokens, and tokens are converted to token IDs.

By the end of this lesson, the first pipeline should feel concrete:

```text
text -> tokens -> token IDs
```

## Why this matters

Tokenization affects:

- how much text fits into the context window;
- how much compute a prompt requires;
- how much latency a request may add;
- how much a token-priced API request may cost;
- how different languages, code, punctuation, accents, whitespace, emojis, and symbols are represented.

Context windows are measured in tokens, not characters or words. More tokens means more context usage, more compute, more latency, and potentially more cost.

!!! tip "Engineering habit"
    Count tokens early when designing prompts, retrieval chunks, and request limits.

## Conceptual explanation

A tokenizer converts text into a sequence of known pieces.

```text
Text:      "Hello, world!"
Tokens:    ["Hello", ",", " world", "!"]
Token IDs: [15496, 11, 995, 0]
```

The exact split and IDs above are illustrative. Different tokenizers can split the same text differently.

A vocabulary is the fixed set of known tokens for a tokenizer/model pair. The tokenizer and model must agree on this vocabulary. If the tokenizer emits ID `42`, the model interprets that ID as row `42` in its embedding table. If the vocabulary does not match, the IDs point to the wrong rows.

!!! note "Key idea"
    Token IDs are arbitrary indices, not semantic magnitudes. ID `100` is not ten times more meaningful than ID `10`, and nearby IDs are not necessarily related.

Tokenization is not understanding. A tokenizer applies a conversion rule. It does not know what the sentence means.

## Minimal math

A text becomes a sequence of tokens:

\[
text \rightarrow [token_0, token_1, \ldots, token_{T-1}]
\]

Tokens become token IDs:

\[
[token_0, token_1, \ldots] \rightarrow [id_0, id_1, \ldots]
\]

The context usage is approximately:

\[
usage = \frac{T}{context\_window}
\]

Here, \(T\) is the token count. If \(T\) grows, the same context window is consumed faster.

## Visual / geometric intuition

Think of the tokenizer as a fixed adapter:

```text
human text
  -> tokenizer
  -> vocabulary entries
  -> integer indices
  -> model input IDs
```

Common text may be represented with larger pieces. Rare text may be split into smaller pieces.

Code, punctuation, accents, whitespace, emojis, symbols, and domain-specific strings can tokenize differently from ordinary English prose. Spanish or other languages may use more or fewer tokens depending on how well the tokenizer vocabulary covers them.

## Implementation model

A tiny tokenizer can be modeled as:

```cpp
std::vector<std::string> tokens = tokenize(text);
std::vector<int> ids = vocabulary.lookup(tokens);
```

The ID is only an index into a vocabulary. It should not be treated as a meaningful numeric feature.

A high-level next-token inference loop looks like this:

```text
text
  -> tokens
  -> token IDs
  -> embeddings
  -> transformer
  -> logits
  -> probabilities
  -> selected next token ID
  -> append to context
  -> repeat
```

This lesson only opens the first part: `text -> tokens -> token IDs`.

## Practical impact

When input exceeds the context window, several things can happen:

- the API or model rejects the request;
- the application truncates the input;
- the application chunks the input;
- the application summarizes earlier material;
- the application uses retrieval later to bring back relevant pieces.

Those strategies are product and system-design choices, but all of them start from token counts.

## Lab walkthrough

Run the [Tokenizer Visualizer Lab](../labs/01-tokenizer-visualizer.md) in `labs/01-tokenizer-visualizer/`.

The lab demonstrates:

- a simple tokenizer;
- an educational BPE-like tokenizer;
- token IDs;
- token count;
- chars/token ratio;
- a context warning.

It is educational and deterministic. It is not a production tokenizer.

## Common confusions

### Does the tokenizer understand meaning?

No. It splits text into vocabulary pieces. Meaning is modeled later by learned vectors and model weights.

### Are token IDs meaningful numbers?

No. Token IDs are indices. Similarity does not live in the ID number.

### Is a token the same as a word?

Not necessarily. A token may be a word, subword, punctuation mark, whitespace-attached piece, byte-like piece, emoji, or symbol.

### Why does Spanish or code sometimes use more tokens?

Token count depends on the tokenizer vocabulary and merge rules. Text that is less common in the tokenizer's training distribution may be split into smaller pieces.

### Why can two models tokenize the same text differently?

They may use different vocabularies, different tokenizer algorithms, or different training data for tokenizer construction.

## Boundaries

This lesson does not explain embeddings, transformer internals, attention, Q/K/V, KV cache internals, or sampling strategies in detail.

## Session summary

### 1. Concepts learned

- LLMs do not consume raw text directly.
- Text becomes tokens, then token IDs.
- A vocabulary is the fixed set of known tokens.
- Token IDs are arbitrary indices, not meanings.
- Context windows are measured in tokens.
- Token count affects context usage, compute, latency, and cost.

### 2. Open questions

- How do production BPE or byte-level tokenizers really work?
- How do token IDs become useful vectors?

### 3. Next concrete step

Read Lesson 02: embeddings.

### 4. Lab connection

- The paired lab makes token splitting and token counts visible.
- The lab stays deterministic so the first pipeline step is easy to inspect.
