# Lab 01 - Tokenizer Visualizer

## Location

`labs/01-tokenizer-visualizer/`

## Lesson link

Read [Lesson 01 - Tokenization](../lessons/01-tokenization.md) first.

## What it demonstrates

- `text -> tokens -> token IDs`;
- token count;
- chars/token ratio;
- simple tokenizer;
- educational BPE-like tokenizer;
- context warning.

## Build and run

From the lab directory:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Example commands:

```bash
./build/tokenizer_visualizer --model bpe --input-file examples/english.txt --lang en
./build/tokenizer_visualizer --model bpe --input-file examples/spanish.txt --lang es
./build/tokenizer_visualizer --model bpe --input-file examples/code.txt --lang code
./build/tokenizer_visualizer --model simple --text "Hello world." --lang en
```

## What to observe

Compare how English, Spanish, code, punctuation, accents, whitespace, emojis, and symbols split into tokens. Watch token counts and chars/token ratio. If the educational context threshold is exceeded, the CLI prints a warning.

## What it is not

- not GPT-2 BPE;
- not a production tokenizer;
- not reversible;
- not optimized.

This lab is educational and deterministic.
