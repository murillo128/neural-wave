# Walkthrough: Lab 02 Embedding Lookup

## What to run

From `labs/02-embedding-lookup/`:

```bash
cmake -S . -B build
cmake --build build
./build/embedding_lookup
```

## What to observe

Look for:

- token strings mapped to token IDs;
- token IDs selecting rows from a small embedding table;
- cosine similarities between manually chosen vectors;
- nearest neighbors such as `cat` near `gato` and `dog`;
- code-like tokens such as `std`, `vector`, `int`, and `string` placed near each other.

The output is designed to reinforce this sentence:

```text
IDs are arbitrary; vectors carry useful relationships.
```

## What the lab is proving

This lab proves the lookup idea:

```text
x = E[token_id]
```

It shows that:

- token IDs are row indices;
- embedding vectors can carry relationships;
- vector similarity is computed from vector components, not from token ID numbers;
- a sequence of token IDs would become a sequence of vectors.

## What it is not proving

This lab is not training embeddings.

It is also not proving that tiny 3D vectors behave like real LLM embeddings. The vectors are manually chosen for readability. Real embeddings are learned and usually much wider.

This lab does not explain attention, Q/K/V, KV cache, RoPE, or training.

## How it connects to the note

Read `notes/02-embeddings.md` first. Then run this lab to see the input embedding side in concrete C++.

The next lab, `labs/03-positional-embeddings/`, adds position to these token vectors.
