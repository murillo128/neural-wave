# neural-wave

`neural-wave` is a lightweight LLM learning book with small C++ labs.

It is not trying to be a production inference engine, a framework, or a survey of every modern technique. Its purpose is to build a clear mental model of how text becomes model input, how vectors flow through the early pipeline, and how token-by-token inference is assembled one lesson at a time.

## Learning philosophy

This repo teaches in a spiral:

1. Learn one idea in plain language.
2. Attach the idea to a tiny amount of math.
3. Build a visual or geometric intuition.
4. Run a small C++ lab that makes the idea concrete.
5. Capture what is known, what is still unknown, and what comes next.

The C++ code is intentionally explicit and didactic. It favors readable loops, named intermediate values, and small examples over abstraction, speed, or production completeness.

## Current milestone

**Milestone 1: token-by-token inference.**

At the current frontier, the repo is building the high-level pipeline:

```text
text -> tokens -> token IDs -> embeddings -> token+position vectors
```

The next lesson will connect those vectors to the outside view of a transformer block, where token representations become contextual. We are not yet opening the transformer internals.

## Current chapters and labs

| Lesson | Chapter | Lab |
| --- | --- | --- |
| 00 | `notes/00-how-to-read-this-repo.md` | Reading guide |
| 01 | `notes/01-tokenization.md` | `labs/01-tokenizer-visualizer/` |
| 02 | `notes/02-embeddings.md` | `labs/02-embedding-lookup/` |
| 03 | `notes/03-positional-information.md` | `labs/03-positional-embeddings/` |

## How notes and labs relate

- `notes/` are book-like chapters. Read these first for the concept, minimal math, mental model, practical impact, boundaries, and session summary.
- `labs/` are runnable C++ demonstrations. Run these after the matching note to see the idea in a tiny executable form.
- Lab walkthroughs explain what to run, what to observe, what the lab proves, and what it does not prove.
- Root files keep the learning path organized:
  - `LEARNING_MAP.md` tracks the current milestone and frontier.
  - `GLOSSARY.md` defines terms at the level currently introduced.
  - `QUESTIONS.md` keeps answered, active, and future questions separated by lesson.

## How to read this repo

1. Start with `notes/00-how-to-read-this-repo.md`.
2. Read `LEARNING_MAP.md` to see the current path.
3. Read one chapter at a time in `notes/`.
4. Run the matching lab in `labs/`.
5. Check `QUESTIONS.md` before jumping ahead.

## Boundaries for the current milestone

To keep the learning path focused, this repo is **not yet** explaining:

- attention internals;
- Q/K/V;
- KV cache internals;
- RoPE math;
- training loops;
- fine-tuning;
- RLHF or DPO;
- RAG implementation details;
- quantization internals.

Some of these terms may appear as future motivation, but the current lessons stop at tokenization, embeddings, and positional information.
