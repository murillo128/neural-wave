# Neural Wave

Neural Wave is a lightweight LLM learning book with small C++ labs. It is designed to build intuition progressively: tokenization, embeddings, positional information, transformer blocks, inference, training, quantization, serving, and agents.

The repository is not a production inference engine or a full framework. It is a structured learning resource for understanding how text becomes model input and how token-by-token inference is assembled one idea at a time.

## Current scope

Current milestone:

**Understanding token-by-token inference.**

Completed / active chapters:

1. Tokenization
2. Embeddings
3. Positional Information

Next:

4. Transformer Block from the Outside

## Repository structure

```text
README.md       repo overview and contributor/developer instructions
docs/           source of truth for the published book
labs/           executable C++ labs
notes/          raw notes, scratchpad, temporary drafts
prompts/        prompts for Codex or future sessions
mkdocs.yml      MkDocs site configuration
```

Public, book-like learning material belongs in `docs/`. Do not maintain duplicate polished lesson copies in `notes/`.

## Documentation site

The book is built with MkDocs Material and MathJax.

Preview locally:

```bash
pip install -r requirements.txt
mkdocs serve
```

Build locally:

```bash
mkdocs build --strict
```

The generated HTML is written to `site/`. Do not commit `site/`.

The generated site is published to GitHub Pages from the `gh-pages` branch by the GitHub Actions workflow in `.github/workflows/docs.yml`.

GitHub repository settings may still need:

```text
Settings -> Pages -> Build and deployment -> Source -> Deploy from a branch
Branch: gh-pages
Folder: / root
```

## Preview the documentation site locally

Install docs dependencies:

```bash
pip install -r requirements.txt
```

Run the local server:

```bash
mkdocs serve
```

Build strictly:

```bash
mkdocs build --strict
```

The generated HTML is written to `site/`. Do not commit `site/`.

## Labs

Executable C++ labs live under `labs/`.

Each lab has its own CMake project and README. The labs are intentionally educational, explicit, and didactic. They are not optimized production implementations, and they do not use Python.

Current labs:

| Lesson | Lab |
| --- | --- |
| 01 - Tokenization | `labs/01-tokenizer-visualizer/` |
| 02 - Embeddings | `labs/02-embedding-lookup/` |
| 03 - Positional Information | `labs/03-positional-embeddings/` |

## Publishing warning

GitHub Pages publishes a static website. Do not put private notes, company-sensitive material, personal context, or private prompts in `docs/`. Only material intended for publication should live under `docs/`.
