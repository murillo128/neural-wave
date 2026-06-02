# Lab 01: Tokenizer Visualizer (Educational)

This lab is an educational C++ tokenizer visualizer that shows:

`text -> tokens -> token ids -> token count -> chars/token ratio`

## Important limitations

- This is educational and deterministic.
- Not production-compatible.
- Not byte-level GPT-2 BPE.
- Not reversible.
- Not optimized.

## Why tokenization matters

LLMs do not read raw text directly. They process token IDs. Tokenization decides how text is split, which directly impacts context usage, latency, and cost.

## Token IDs and context windows

Each token maps to an integer ID from a vocabulary. Context windows are measured in tokens, not characters. Fewer tokens for the same text can improve effective capacity.

This lab includes an educational context threshold:

- `kEducationalContextLimit = 32`
- If exceeded, the CLI prints a warning and continues.

## Tokenizers in this lab

1. **simple**: rule-based split by punctuation/space.
2. **bpe**: tiny deterministic merge-list over UTF-8 code points.


## Connection to next-token inference

This lab only visualizes the tokenization part. In a real LLM, the produced token IDs would be fed into an embedding table. The transformer would output logits over the same fixed vocabulary. A decoder would choose the next token ID and append it to the context.

## Key lesson

- Token IDs are arbitrary indices.
- The tokenizer does not understand meaning.
- Same text can have different token counts depending on the tokenizer.
- Token count affects context, latency, and cost.

## Build

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Example commands

```bash
./build/tokenizer_visualizer --model bpe --input-file examples/english.txt --lang en
./build/tokenizer_visualizer --model bpe --input-file examples/spanish.txt --lang es
./build/tokenizer_visualizer --model bpe --input-file examples/code.txt --lang code
./build/tokenizer_visualizer --model simple --text "Hello world." --lang en
```
