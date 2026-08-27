# Neural Wave

Neural Wave is a conceptual reference for understanding large language models: what the main mechanisms are, why they work, how they fit together, and where the mathematics is useful.

The repository is intentionally organized as an evolving knowledge base rather than a course with exercises.

## The core computational spine

A decoder-only language model can be viewed at first pass as this pipeline:

```text
text
  -> tokenizer
  -> token IDs
  -> embedding vectors
  -> residual stream
  -> transformer blocks
       - attention: communication across positions
       - MLP: transformation within each position
       - normalization + residual updates
  -> final hidden representation
  -> vocabulary projection (lm_head)
  -> logits
  -> decoding
  -> next token
```

Training determines the weights that make those transformations useful. Post-training changes how the learned model behaves. Retrieval, tools, agents, and external memory add systems around the base model rather than changing this basic spine.

## Current conceptual pages

### Foundations

- [Tokenization](foundations/tokenization.md) — how text becomes discrete model symbols and why tokenization affects the rest of the system.
- [Embeddings and Representation Geometry](foundations/embeddings-and-representation-geometry.md) — how arbitrary token IDs become learned vectors and how to think about vector geometry without over-interpreting it.

### Transformer core

- [Positional Information](transformers/positional-information.md) — why order must enter the computation and how absolute position, sinusoidal methods, RoPE, and attention biases differ conceptually.
- [Transformer Block and Residual Stream](transformers/transformer-block.md) — the outside view of attention, MLPs, normalization, residual connections, and contextual representations.

## How to use the reference

Do not wait to finish all of linear algebra, probability, optimization, or transformer internals before looking at the whole model. Start with the mechanism you need, build a useful mental model, then revisit it when another part of the system creates a reason to go deeper.

The [Learning Map](learning-map.md) shows the wider field and the current depth of coverage. It is descriptive, not a task checklist. The [Glossary](glossary.md) is useful when a term appears before its dedicated treatment.

Practical infrastructure, benchmarks, hardware experiments, implementation labs, and deployment workflows are intentionally outside the scope of this repository except when a small practical consequence helps explain a concept.
