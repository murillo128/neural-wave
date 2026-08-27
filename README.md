# Neural Wave

Neural Wave is a persistent, structured knowledge base for understanding the theory and concepts behind large language models.

It is meant to behave like a small evolving textbook and personal reference: explanations are organized by concept, consolidated in place, and deepened over time rather than stored as a sequence of sessions.

## Scope

The repository focuses on:

- conceptual understanding and mental models;
- mathematical foundations when they genuinely clarify a mechanism;
- geometric and visual intuition;
- transformer architecture and representation flow;
- pretraining, post-training, inference, retrieval, and evaluation concepts;
- differences between model architectures and model families;
- agents and world models;
- practical, product, and infrastructure implications only when they help explain the underlying mechanism.

It is **not** primarily a repository for labs, implementation exercises, benchmark scripts, local inference experiments, hardware experiments, or serving/deployment workflows. Those activities belong in other projects. Material removed during this refocus remains available through git history.

## Learning model

The material follows a spiral rather than a strict prerequisite ladder. Important topics can be revisited at increasing depth:

1. build an intuitive mental model;
2. add the minimum useful formalization;
3. return with deeper mathematics where it pays off;
4. connect the mechanism to neighboring components;
5. understand its practical consequences.

Individual pages do not need to follow that sequence mechanically. The goal is clarity, not a template.

Knowledge should be consolidated into stable thematic pages. This repository is not a conversation archive, session log, open-question dump, or project-management tracker.

## Navigation

- [Learning Map](docs/learning-map.md) — a conceptual map of the field, relationships between areas, and the current depth of coverage.
- **Foundations**
  - [Tokenization](docs/foundations/tokenization.md)
  - [Embeddings and Representation Geometry](docs/foundations/embeddings-and-representation-geometry.md)
- **Transformer Core**
  - [Positional Information](docs/transformers/positional-information.md)
  - [Transformer Block and Residual Stream](docs/transformers/transformer-block.md)
- [Glossary](docs/glossary.md) — compact definitions for recurring terms.

The MkDocs site provides the same material with book-style navigation and rendered mathematics.

## Maintenance principle

When understanding of a concept improves, update or extend the existing conceptual page when possible. Prefer one evolving explanation over multiple chronological notes. New files should represent durable conceptual boundaries, not individual conversations or exercises.

## License

MIT. See [LICENSE](LICENSE).
