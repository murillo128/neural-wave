# 01 - Tokenization: text to token IDs

## Goal

Understand that LLMs do not consume raw text directly. Before inference begins, text is converted into tokens, and tokens are converted into token IDs.

By the end of this lesson, the pipeline should feel concrete:

```text
text -> tokens -> token IDs
```

This is the first interface between human-readable text and the numeric machinery of a language model.

## Why this matters

Tokenization affects almost everything that happens later:

- how much text fits into the context window;
- how much work the model does for a prompt;
- how much an API request may cost;
- how fast a response can start and continue;
- how prompts, code, multilingual text, punctuation, accents, and symbols are represented.

A model does not see "characters" or "words" in the ordinary human sense. It sees a sequence of token IDs chosen by a tokenizer that must match the model's vocabulary.

## Conceptual explanation

A tokenizer is a component that converts text into a sequence of known pieces.

Example:

```text
Text:      "Hello, world!"
Tokens:    ["Hello", ",", " world", "!"]
Token IDs: [15496, 11, 995, 0]
```

The exact tokens and IDs above are only illustrative. Different tokenizers can split the same text differently, and therefore produce different token counts.

A tokenizer may use whole words, subwords, bytes, punctuation pieces, spaces attached to words, or other patterns. Modern LLM tokenizers often use subword-like pieces so common text can be compact while rare text can still be represented by smaller pieces.

Important: tokenization does not mean understanding. The tokenizer is not deciding what the sentence means. It is applying a fixed conversion rule so the model can receive IDs from a known vocabulary.

## Minimal math

Let text be converted into `T` tokens:

```text
text -> [token_0, token_1, ..., token_(T-1)]
```

Each token is mapped to an integer ID:

```text
[token_0, token_1, ..., token_(T-1)]
  -> [id_0, id_1, ..., id_(T-1)]
```

The number `T` is the sequence length. Context windows are measured in tokens, so `T` is already an important resource before any embedding or transformer work begins.

## Mental model

Think of tokenization as a fixed dictionary interface:

```text
human text
  -> tokenizer
  -> vocabulary entries
  -> integer indices
  -> model input IDs
```

The tokenizer is like an adapter. It turns messy text into IDs from a finite set that the model knows how to process.

If the tokenizer sees very common text, it may use larger pieces. If it sees rare text, unusual symbols, accents, code fragments, or domain-specific strings, it may split them into smaller pieces.

## Token IDs are arbitrary

Token IDs are indices, not semantic numbers.

If a vocabulary contains:

```text
cat   -> 17
gato  -> 913
dog   -> 18
house -> 204
```

that does not mean:

- `cat` is semantically close to `dog` because `17` and `18` are nearby;
- `gato` is more "important" than `cat` because `913` is larger;
- arithmetic on token IDs has language meaning.

The useful relationships appear later in embedding vectors, not in the raw ID numbers.

## Vocabulary as fixed interface between tokenizer and model

A tokenizer and model share a fixed vocabulary. The tokenizer must produce IDs that the model's embedding table understands.

This matters because:

- the tokenizer decides which token IDs appear;
- the model has learned parameters associated with those IDs;
- changing the tokenizer changes the interface to the model;
- a token ID only makes sense relative to the vocabulary it belongs to.

A vocabulary is not a complete dictionary of meaning. It is a fixed set of pieces the tokenizer is allowed to emit.

## Multilingual and domain effects

Tokenization efficiency depends on the language and domain.

The same tokenizer may behave differently for:

- English words;
- Spanish words and accents;
- punctuation-heavy text;
- emoji and symbols;
- C++ code such as `std::vector<int>`;
- rare names;
- unusual identifiers;
- domain-specific terms.

For example, a common English word may be one token, while an accented word or a rare technical identifier may be split into several smaller pieces. Code often contains punctuation, casing, underscores, templates, and symbols, so its token count can differ sharply from prose.

This does not mean the model cannot handle the text. It means the text may consume more tokens.

## Context windows are measured in tokens

A context window is the maximum number of tokens the model can process in a request. It is not measured in characters, words, paragraphs, or pages.

This distinction matters:

```text
short-looking text with rare symbols -> many tokens
long-looking common prose           -> sometimes fewer tokens than expected
```

Two prompts with the same character count can use different amounts of context if they tokenize differently.

## What happens when text exceeds context

If the tokenized input is longer than the model's context window, the full text cannot be processed as one sequence.

Depending on the system, one of several things may happen:

- the request is rejected;
- the input is truncated;
- older tokens are dropped;
- the application must split or summarize text before sending it.

For now, the key idea is simple: exceeding context is a token-count problem. Later, this becomes important for chunking, retrieval, memory strategies, and long-context systems.

## Connection to next-token inference

At a high level, autoregressive generation repeats this loop:

```text
text
  -> tokens
  -> token IDs
  -> embeddings
  -> transformer
  -> logits
  -> probabilities
  -> next token
  -> append
  -> repeat
```

This lesson only covers the first part:

```text
text -> tokens -> token IDs
```

The next lessons explain embeddings and positional information before we look at the transformer block from the outside.

## Implementation summary for `labs/01-tokenizer-visualizer`

The lab in `labs/01-tokenizer-visualizer/` makes tokenization visible.

It demonstrates:

- converting input text into tokens;
- assigning token IDs from a tiny vocabulary;
- comparing token counts across examples;
- seeing how English, Spanish, code, punctuation, accents, and symbols can split differently;
- warning when an educational context threshold is exceeded.

The lab includes two intentionally small tokenizer modes:

- `simple`: a rule-based educational splitter;
- `bpe`: a tiny deterministic merge-list tokenizer over UTF-8 code points.

These are teaching tools. They are not production tokenizers and are not intended to match a modern commercial model exactly.

## Practical impact

### Cost

Many LLM products price work by tokens. More input tokens can mean higher prompt cost, and more generated tokens can mean higher output cost.

### Latency

More tokens usually mean more model work. Long prompts can take longer to process before the model begins producing output.

### Context capacity

Every token uses part of the context window. Token-heavy text leaves less room for instructions, examples, documents, and generated output.

### Prompt design

Prompt wording matters partly because it changes token usage. A concise prompt can fit more task-relevant information into the same context window.

### RAG/chunking later

Retrieval-augmented generation and chunking are later topics. Tokenization matters there because chunks must fit into a token budget, not just a character budget.

### Multilingual/code efficiency

Some languages, scripts, and code patterns may use more tokens than others with a given tokenizer. This can affect cost, latency, and how much content fits into context.

## Common confusions

### "Does tokenization mean the model understands the text?"

No. Tokenization is conversion, not understanding. It prepares IDs that the model can process.

### "Are token IDs meaningful numbers?"

No. Token IDs are arbitrary vocabulary indices. The number itself is not a semantic coordinate.

### "Does every word become one token?"

No. A word may become one token, many tokens, or share tokens with spaces or punctuation depending on the tokenizer.

### "Can different tokenizers produce different token counts?"

Yes. The same text can have different token counts under different tokenizers.

### "Is unknown text impossible?"

Usually no. Modern tokenizers can often fall back to smaller pieces, bytes, or unknown-token mechanisms. Rare text may simply become less compact.

## Boundaries

This lesson intentionally stops before later internals:

- no embedding geometry beyond the fact that token IDs are looked up later;
- no attention internals;
- no Q/K/V;
- no KV cache internals;
- no RoPE math;
- no training loop;
- no fine-tuning or RLHF;
- no RAG implementation;
- no quantization internals.

## Session summary

### 1. Concepts learned

- LLMs do not consume raw text directly.
- A tokenizer converts text into tokens and token IDs.
- Token IDs are arbitrary indices, not semantic numbers.
- A fixed vocabulary is shared by the tokenizer and model.
- Unknown or rare text may be split into smaller pieces.
- Different tokenizers can produce different token counts for the same text.
- Context windows are measured in tokens.
- Token count affects context usage, latency, and cost.
- Tokenization does not mean understanding.
- The high-level generation loop appends one predicted token at a time.

### 2. Open questions

- How does a token ID become a vector?
- Where do useful relationships between tokens live if IDs are arbitrary?
- How does the model choose the next token after it has token IDs?

### 3. Next concrete step

Read Lesson 02, `notes/02-embeddings.md`, and run `labs/02-embedding-lookup/` to see token IDs become vectors.

### 4. Repo changes

- Expanded `notes/01-tokenization.md` into a full chapter.
- Connected the chapter to `labs/01-tokenizer-visualizer/`.
- Set the boundary for what tokenization explains and what remains for later lessons.
