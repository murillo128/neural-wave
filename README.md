# neural-wave

This repository originally started years ago as a neural network experimentation project. It is now being repurposed as a structured **LLM learning lab** focused on building deep intuition through clear theory and hands-on implementation.

## Learning goals

The goal is to deeply understand:

- tokenization
- embeddings
- transformers
- inference
- KV cache
- quantization
- training
- fine-tuning
- RLHF / DPO
- RAG
- serving
- hardware execution
- providers
- agents
- world models

## Repository organization

This repository is intentionally split into two layers:

1. **Theory / learning structure** at the repository root:
   - `README.md`
   - `LEARNING_MAP.md`
   - `GLOSSARY.md`
   - `QUESTIONS.md`
   - `prompts/`
   - `notes/`
2. **Hands-on executable labs** under:
   - `labs/`

This separation is intentional and should remain strict so learning material stays organized and labs remain practical and runnable.

## Current milestone

**Milestone 1: Understanding token-by-token inference.**

Active labs:

- `labs/01-tokenizer-visualizer/`
- `labs/02-embedding-lookup/`

## How to use this repo

1. Start from `LEARNING_MAP.md` for current direction.
2. Use `prompts/` to structure study sessions.
3. Capture understanding in `notes/`.
4. Build and run labs in `labs/`.
