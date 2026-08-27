# Learning Map

This page is a conceptual map of the LLM field, not a syllabus or task tracker. The areas below are tightly coupled: the repository should revisit them in a spiral rather than finish one entire layer before touching the next.

## The field at a glance

```text
                         mathematical foundations
                  linear algebra · probability · optimization
                                   |
                                   v
text/data -> tokenization -> embeddings / representation geometry
                                   |
                    positional information
                                   |
                                   v
                         residual stream
                                   |
                         transformer stack
                    +--------------+--------------+
                    |                             |
                 attention                       MLP
          communication across tokens     feature transformation
                    |                             |
                    +--------------+--------------+
                                   |
                                   v
                         final representation
                                   |
                           lm_head / logits
                                   |
                              decoding
                                   |
                              next token

pretraining objective + data + optimization  ---> learns the base weights
post-training (SFT / RLHF / DPO / ...)       ---> shapes behavior and preferences
RAG / external memory                        ---> supplies information at inference time
agents                                       ---> add tools, state, control loops and actions
world models                                 ---> learn predictive state useful for planning/control
evals                                        ---> measure every layer above
```

The diagram is deliberately simplified. Modern systems branch into dense and sparse architectures, different attention mechanisms, multimodality, recurrent or state-space components, retrieval, tool use, and many post-training recipes. The map below makes those branches explicit.

## 1. Mathematical foundations

These are supporting tools, not a separate gate that must be completed first.

**Linear algebra** explains vectors, matrices, projections, dot products, changes of basis, low-rank structure, and the geometry of representations. It becomes especially useful for embeddings, attention, MLPs, normalization, and quantization.

**Probability and information theory** explain likelihood, softmax distributions, cross-entropy, entropy, KL divergence, sampling, calibration, and many post-training objectives.

**Calculus and optimization** explain gradients, backpropagation, stochastic gradient descent, Adam-like optimizers, learning-rate schedules, and why training changes billions of parameters coherently.

**Statistics and experimental reasoning** matter for scaling laws, eval design, benchmark interpretation, ablations, and distinguishing real gains from noise or contamination.

Current depth: the repository already uses basic vector geometry and softmax notation, but these foundations have not yet received dedicated pages.

## 2. Tokens, embeddings, and representations

This is the interface between symbolic text and continuous model computation.

- **Tokenization** chooses the discrete units the model sees.
- **Token IDs** are arbitrary vocabulary indices.
- **Embeddings** map those indices into learned vectors.
- **Representation geometry** gives us ways to reason about directions, similarity, features, and subspaces without pretending that every coordinate has a human-readable meaning.
- **Contextual representations** emerge after transformer layers let each position depend on other positions.

Current depth: first-pass pages exist for [tokenization](foundations/tokenization.md) and [embeddings / representation geometry](foundations/embeddings-and-representation-geometry.md). A later pass should deepen tokenizer training, byte-level schemes, embedding anisotropy, feature superposition, probing, and representation evolution across layers.

## 3. Transformer core

The transformer stack repeatedly updates a sequence of hidden vectors while usually preserving the matrix shape \(T \times d\).

Important components are:

- **residual stream** — the evolving shared representation carried through the network;
- **attention** — lets information move between token positions;
- **Q/K/V projections** — define what each position queries for, how other positions are matched, and what content is transferred;
- **causal masking** — prevents a decoder-only model from reading future tokens during next-token training and generation;
- **MLPs / feed-forward layers** — transform features independently at each position after information has been mixed;
- **normalization** — controls scale and stabilizes deep computation;
- **positional information** — makes sequence order available to the model;
- **RoPE and related schemes** — inject position into attention geometry in many modern LLMs.

Current depth: [positional information](transformers/positional-information.md) has a first pass and [the transformer block / residual stream](transformers/transformer-block.md) provides the outside view. Attention internals, Q/K/V mathematics, feature superposition, MLP interpretation, and normalization deserve deeper passes later.

## 4. Pretraining and next-token prediction

A base autoregressive LLM is typically trained to predict the next token given previous tokens. That simple local objective creates pressure to learn syntax, semantics, factual regularities, program structure, long-range dependencies, and useful internal abstractions because all of them improve prediction.

Topics in this area include:

- next-token likelihood and cross-entropy;
- teacher forcing and causal training;
- backpropagation through the transformer;
- data mixtures and data quality;
- optimization dynamics;
- scaling laws and compute/data/model tradeoffs;
- emergence and smooth versus threshold-like capability changes;
- in-context learning and why a fixed set of weights can adapt behavior from the prompt.

Current depth: mapped, but not yet developed as a standalone conceptual section.

## 5. Post-training

Pretraining gives a capable predictor; post-training shapes how that capability is exposed and controlled.

The main families to connect are:

- **SFT** — supervised fine-tuning on desired input/output behavior;
- **RLHF** — preference modeling plus reinforcement-learning-style optimization;
- **DPO and related preference objectives** — optimize chosen versus rejected responses more directly;
- **distillation** — transfer behavior or knowledge from a stronger teacher into another model;
- **reasoning training** — methods that encourage useful intermediate computation, verification, search, or long-horizon problem solving;
- **tool-use and agentic post-training** — teach models when and how to interact with external systems.

A deeper treatment should separate the mathematical objective from the behavioral effect: two methods can produce similar product behavior through very different optimization paths.

Current depth: mapped, not yet developed.

## 6. Inference and decoding

Inference is the same learned network used in a different computational regime from training.

Important concepts are:

- **logits and softmax** — convert the final hidden state into a distribution over the vocabulary;
- **greedy decoding, temperature, top-k, top-p and other sampling rules** — choose the next token from that distribution;
- **prefill** — process the existing prompt/context;
- **decode** — generate new tokens autoregressively, one step at a time in the basic formulation;
- **KV cache** — reuse attention state from previous positions instead of recomputing it on every decode step;
- **speculative and multi-token methods** — reduce the sequential cost of generation while preserving or approximating the target distribution.

Batching, memory bandwidth, cache layout, and serving systems matter here only when they illuminate why the computation behaves as it does. Operational benchmarking belongs elsewhere.

Current depth: logits/softmax are introduced through the representation page; the rest is mapped for later conceptual treatment.

## 7. Alternative and sparse architectures

"LLM" does not imply one exact transformer configuration.

Important architectural branches include:

- **dense transformers** versus **Mixture-of-Experts (MoE)** models;
- full multi-head attention versus **MQA/GQA** and other KV-sharing schemes;
- standard MLPs versus gated MLPs and expert routing;
- transformer/recurrent/state-space hybrids;
- multimodal encoders, decoders, projectors, and shared latent spaces;
- long-context mechanisms and memory-augmented variants.

For MoE in particular, distinguish total parameter count from active parameters per token. Sparse routing changes compute, memory traffic, capacity, specialization, and serving behavior without changing the basic idea that a token representation is repeatedly transformed.

Current depth: mapped, not yet developed.

## 8. Retrieval, memory, and evaluation

**RAG** keeps the model weights fixed while adding relevant external information to the context. It should be understood as a retrieval-and-conditioning system, not as a substitute term for learning.

**Evals** are cross-cutting. They measure capabilities, regressions, preferences, robustness, calibration, tool use, factuality, latency/cost tradeoffs, and domain-specific success. Good eval design requires understanding what is actually being measured and what the benchmark can be gamed by.

Current depth: mapped, not yet developed.

## 9. Agents

An agent is usually not a different neural architecture. It is a system around a model that repeatedly observes state, chooses an action, uses tools or external memory, observes the result, and continues until a stopping condition.

The important conceptual questions are therefore about:

- planning versus reactive tool use;
- state and memory;
- tool interfaces and action spaces;
- verification and feedback loops;
- error accumulation over long horizons;
- whether reasoning lives in model activations, textual scratch space, external state, or some combination.

Current depth: mapped, not yet developed.

## 10. World models

A world model learns a representation that is useful for predicting how some environment evolves, often in a latent state space rather than directly predicting the next text token.

The key contrast with a conventional autoregressive LLM is not simply "video versus text". It is the learned object and training pressure: a world model is explicitly organized around state, dynamics, prediction, and often planning/control, while a language model is organized around predicting tokens. The two ideas can overlap: LLMs can learn implicit world structure, and language or multimodal systems can incorporate latent predictive models.

Current depth: mapped, not yet developed.

## 11. Model families and providers

Comparing models should separate several axes that are often collapsed into one leaderboard number:

- parameter count and active parameter count;
- dense versus MoE routing;
- tokenizer and vocabulary;
- context and positional scheme;
- attention/KV architecture;
- multimodal components;
- pretraining data and objective choices;
- post-training recipe;
- reasoning/tool-use behavior;
- quantization and inference format;
- openness of weights, tokenizer, training details, and serving stack.

Provider comparisons should distinguish architectural differences from product differences such as API limits, tool integrations, safety layers, pricing, and serving optimizations.

Current depth: mapped, not yet developed.

## Current coverage in one view

| Area | Current depth in this repository | Natural deeper pass |
| --- | --- | --- |
| Tokenization | First-pass conceptual page | BPE/Unigram construction, byte fallback, vocabulary tradeoffs |
| Embeddings & geometry | First-pass conceptual page | anisotropy, superposition, layer-wise representations, probing |
| Positional information | First-pass conceptual page | RoPE mathematics, scaling/extrapolation, relative position |
| Transformer block | Outside-view conceptual page | Q/K/V attention math, residual-stream analysis, MLP/norm details |
| Training & scaling | Field map only | next-token objective, gradients, optimization, scaling laws, ICL |
| Post-training | Field map only | SFT, RLHF, DPO, distillation, reasoning training |
| Inference | Logits/softmax bridge + field map | decoding, prefill/decode, KV cache, speculative methods |
| Architectures | Field map only | MoE, GQA/MQA, hybrids, multimodality |
| RAG & evals | Field map only | retrieval geometry, chunking as context, eval design |
| Agents & world models | Field map only | control loops, memory, latent dynamics, planning |
| Model/provider differences | Field map only | systematic architecture and training comparisons |

The table records depth, not priority. A useful future explanation may jump between rows whenever a connection makes another concept easier to understand.
