# 00 - How to read this repo

## Goal

Use this repository as a short technical book with runnable C++ labs, not as a pile of disconnected notes.

The learning path is intentionally progressive. Each lesson should leave you with a useful mental model, a tiny implementation model, and a clear boundary around what has not been explained yet.

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

Later chapters can revisit earlier ideas with more detail. For example, tokenization first appears as a practical interface, then later becomes relevant to cost, context limits, chunking, serving, and product behavior.

## What each lesson should contain

Each lesson should be readable as a small chapter. The preferred structure is:

1. **Conceptual explanation**: the idea in plain language.
2. **Minimal math**: only the notation needed to reason clearly.
3. **Visual or geometric intuition**: shapes, tables, vectors, or simple diagrams.
4. **Implementation model**: how the idea appears in simple C++ data structures and loops.
5. **Practical impact**: why the idea matters for cost, latency, prompts, context, or model behavior.
6. **Lab walkthrough**: what to run and what to observe.
7. **Session summary**:
   - Concepts learned.
   - Open questions.
   - Next concrete step.
   - Repo changes.

This structure is a guide, not a rigid template, but every lesson should end with the same four-part session summary.

## How to use the labs

The labs are intentionally tiny and educational.

They are designed to answer questions like:

- What does this concept look like in memory?
- What are the shapes of the data?
- Which values are arbitrary IDs, and which values are meaningful vectors?
- What changes when a token appears in a different position?

They are not designed to be fast, complete, or production-compatible.

## C++ style in this repo

C++ code should be explicit and didactic:

- Prefer simple data structures such as `std::vector`, `std::unordered_map`, and small structs.
- Prefer named intermediate values over clever one-liners.
- Prefer direct loops over abstractions that hide the concept being taught.
- Avoid heavyweight dependencies unless a lab truly needs them.
- Keep output text educational, so running a lab explains what to look for.

The point is not to impress C++ experts. The point is to make LLM mechanics inspectable.

## Boundaries

Do not jump ahead just because a later term is nearby. In the current milestone, we are not yet explaining attention internals, Q/K/V, KV cache internals, RoPE math, training, fine-tuning, RLHF, RAG implementation, or quantization internals.

Those topics will be easier once the early pipeline is solid.
