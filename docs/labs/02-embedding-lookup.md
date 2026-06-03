# Lab 02 - Embedding Lookup

## Location

`labs/02-embedding-lookup/`

## Lesson link

Read [Lesson 02 - Embeddings](../lessons/02-embeddings.md) first.

## What it demonstrates

- token -> ID;
- ID -> vector;
- dot product;
- norm;
- cosine similarity;
- nearest neighbors.

## Build and run

From the lab directory:

```bash
cmake -S . -B build
cmake --build build
./build/embedding_lookup
```

## What to observe

Look for the token ID, the selected vector, vector norms, cosine similarity values, and nearest neighbors. The ID is an index. The vector is where geometric comparison starts.

## What it is not

- vectors are manually chosen;
- no training;
- no transformer;
- no contextual embeddings.
