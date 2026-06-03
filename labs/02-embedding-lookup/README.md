# Lab 02: Embedding Lookup

This lab demonstrates the first learned lookup step in a language model:

```text
x = E[token_id]
```

`E` is an embedding table. A token ID selects one row, and that row is the vector representation passed to later model layers.

## Key idea

Token IDs are arbitrary. The model should not treat the integer value itself as semantic information. Instead, the token ID is only an index into the embedding table.

For example, if `cat` has token ID `0` and `house` has token ID `3`, that does not mean `cat` and `house` are numerically or semantically related because `0` and `3` are close. Their relationship comes from the vectors stored in the embedding table.

## Important limitation

The vectors in this lab are manually chosen 3D examples. They are not learned. Real model embeddings are learned during training and are usually much larger.

## What the executable shows

The program prints:

- token string -> token ID -> vector lookup examples
- dot-product-based cosine similarities
- nearest neighbors by cosine similarity

The vocabulary is intentionally small:

```text
cat, gato, dog, house, std, vector, int, string
```

`cat`, `gato`, and `dog` are placed close together. `std`, `vector`, `int`, and `string` are placed close together. `house` is placed in a different direction.

## Build and run

```bash
cmake -S . -B build
cmake --build build
./build/embedding_lookup
```
