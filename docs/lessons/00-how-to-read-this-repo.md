# 00 - How to Read This Repo

## Goal

Use this repository as a short technical book with runnable C++ labs, not as a pile of disconnected notes.

This is a book + lab. The lessons build the conceptual path; the labs make each idea visible in a tiny executable program.

!!! note "Learning style"
    We intentionally do not master one complete layer before touching the next. We move in a spiral.

## Spiral learning approach

LLMs are too large to understand all at once. This repo uses a spiral approach:

1. Start with the outside shape of the system.
2. Learn one small mechanism.
3. Build a minimal lab for that mechanism.
4. Return to the larger system with one more piece understood.
5. Repeat.

The current spiral is:

```text
text
  -> tokens
  -> token IDs
  -> embeddings
  -> token + position vectors
  -> later: contextual vectors
```

## How lessons should read

Lessons should stay readable. A chapter should distinguish:

- conceptual explanation;
- minimal math;
- visual or geometric intuition;
- implementation model;
- practical impact.

Mathematical notation should be minimal but precise. Use formulas when they remove ambiguity, not to make the lesson look more advanced.

## How labs should behave

Labs are intentionally tiny. They should answer questions like:

- What does this concept look like in memory?
- What are the shapes of the data?
- Which values are arbitrary IDs, and which values are meaningful vectors?
- What changes when a token appears in a different position?

C++ code should be explicit and didactic, not optimized. Prefer readable loops, named intermediate values, and small examples over clever abstractions.

## Session summary convention

Each session should end with:

1. Concepts learned.
2. Open questions.
3. Next concrete step.
4. Repo changes.

This keeps the learning path progressive and makes future sessions easier to resume.

## Boundaries

Do not jump ahead just because a later term is nearby. In the current milestone, we are not yet explaining attention internals, Q/K/V, KV cache internals, RoPE math, training, fine-tuning, RLHF, RAG implementation, or quantization internals.

Those topics will be easier once the early pipeline is solid.
