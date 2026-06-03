# Walkthrough: Lab 03 Positional Embeddings

## What to run

From `labs/03-positional-embeddings/`:

```bash
cmake -S . -B build
cmake --build build
./build/positional_embeddings
```

## What to observe

Look for each row printed by the program:

- token;
- position;
- token embedding;
- position embedding;
- final input vector.

Compare `dog` in:

```text
dog bites man
man bites dog
```

The token embedding for `dog` stays the same, but the final vector changes when the position changes.

## What the lab is proving

This lab proves the simplified construction:

```text
X_i = E(token_i) + P(i)
```

It shows that:

- token identity and position can be combined by vector addition;
- token embedding and position embedding must have the same width;
- the final sequence shape remains `T x hidden_size`;
- the same token embedding can produce different final vectors at different positions.

## What it is not proving

This lab is not training positional embeddings.

It is also not explaining:

- attention internals;
- Q/K/V;
- KV cache internals;
- RoPE math;
- full contextual understanding.

After this lab, each row knows token identity plus position, but not yet full context.

## How it connects to the note

Read `notes/03-positional-information.md` first. Then run this lab to see the table from the chapter implemented in C++.

Lesson 04 will explain, from the outside, how token+position vectors become contextual vectors.
