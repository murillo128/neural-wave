# Walkthrough: Lab 01 Tokenizer Visualizer

## What to run

From `labs/01-tokenizer-visualizer/`:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Then try several inputs:

```bash
./build/tokenizer_visualizer --model bpe --input-file examples/english.txt --lang en
./build/tokenizer_visualizer --model bpe --input-file examples/spanish.txt --lang es
./build/tokenizer_visualizer --model bpe --input-file examples/code.txt --lang code
./build/tokenizer_visualizer --model simple --text "Hello, world!" --lang en
```

## What to observe

Look for:

- the original text;
- the token pieces;
- the token IDs;
- the token count;
- differences between English, Spanish, code, punctuation, accents, and symbols;
- any warning when the educational context threshold is exceeded.

The exact IDs are not meanings. They are vocabulary indices.

## What the lab is proving

This lab proves the first interface in the LLM pipeline:

```text
text -> tokens -> token IDs
```

It shows that:

- LLM input starts as token IDs, not raw text;
- token IDs are arbitrary;
- different tokenization rules can produce different token counts;
- token count is the unit that matters for context usage.

## What it is not proving

This lab is not proving that the tokenizer understands the text.

It is also not:

- a production tokenizer;
- a byte-compatible GPT tokenizer;
- a reversible tokenizer;
- an optimized tokenizer;
- a model inference engine.

## How it connects to the note

Read `notes/01-tokenization.md` first. Then run this lab to make the chapter's claims visible in C++ output.

The next lab, `labs/02-embedding-lookup/`, starts where this one stops: token IDs become vectors.
