# Glossary

Compact definitions for terms used across the reference. Definitions should become more precise as their dedicated conceptual pages deepen.

## Agent

A system that places a model inside a control loop: observe state, choose an action, use tools or external memory, observe the result, and continue until a stopping condition.

## Attention

A mechanism that lets one token position compute a weighted combination of information from other positions. In decoder-only LLMs it is normally constrained by a causal mask.

## Autoregressive model

A model that factorizes a sequence probability into predictions conditioned on earlier elements and can generate by repeatedly predicting the next token.

## BPE — Byte Pair Encoding

A family of subword tokenization methods that learns a vocabulary by repeatedly merging frequent adjacent symbol pairs. Many practical tokenizers combine BPE-like merges with byte-level coverage.

## Causal mask

A restriction in decoder self-attention that prevents position \(i\) from attending to future positions \(j > i\).

## Context window

The amount of token context the model can process under a particular model/configuration. A larger advertised context does not imply equal quality at every distance.

## Contextual representation

A hidden vector whose value depends on the surrounding sequence after information has flowed through model layers.

## Cosine similarity

A normalized comparison of vector direction:

\[
\mathrm{cos}(a,b)=\frac{a\cdot b}{\|a\|\|b\|}
\]

Useful as a geometric probe, but not a complete description of how a model represents meaning.

## Cross-entropy

A loss used to compare a target distribution with a model distribution. Next-token pretraining commonly minimizes cross-entropy against the observed next token.

## Decode phase

The autoregressive generation phase after the prompt has been processed. In the basic formulation, one new token is produced per model step.

## Decoding / sampling

The rule used to turn next-token logits or probabilities into a chosen next token. Examples include greedy decoding, temperature scaling, top-k, and top-p sampling.

## Distillation

Training one model to reproduce useful behavior, distributions, or intermediate signals from another model or ensemble.

## DPO — Direct Preference Optimization

A preference-training approach that directly increases the relative likelihood of preferred responses over rejected responses under a reference-aware objective, without requiring the classic reward-model-plus-RL pipeline.

## Dot product

A bilinear comparison of two vectors:

\[
a\cdot b=\sum_i a_i b_i
\]

It is central to attention and many geometric interpretations.

## Embedding

A learned vector associated with a discrete item such as a token ID. Initial token embeddings are non-contextual; later hidden representations are contextual.

## Embedding table

A learned matrix \(E\in\mathbb{R}^{V\times d}\) with one row per vocabulary item and hidden width \(d\).

## Eval

A measurement procedure for a model or system: capability benchmarks, preference tests, robustness checks, domain tasks, regression suites, calibration, tool-use success, or other defined outcomes.

## Fine-tuning

Additional parameter training starting from a pretrained model. The term covers many objectives; SFT and preference optimization are specific forms.

## Greedy decoding

Always choosing the token with the highest current score/probability.

## Hidden size

The width \(d\) of the residual-stream vector at each token position.

## In-context learning

Behavioral adaptation from examples or instructions in the prompt without changing the model weights during that interaction.

## KV cache

Cached keys and values from previous attention positions, reused during autoregressive decoding so the model does not recompute the full past attention state at every new token.

## Logit

A raw, unnormalized score for a candidate output token before softmax.

## `lm_head`

The final vocabulary projection that maps a hidden representation to one logit per vocabulary item. It may share weights with the input embedding table.

## MLP / feed-forward network

The per-position nonlinear transformation inside a transformer block. The same MLP weights are applied independently to each token position; modern LLMs often use gated variants such as SwiGLU.

## MoE — Mixture of Experts

A sparse architecture in which a router selects a subset of expert networks for each token. Total parameters can be much larger than the parameters active for a single token.

## MQA / GQA

Multi-Query Attention and Grouped-Query Attention share key/value projections across multiple query heads to reduce KV-cache size and memory traffic compared with fully independent K/V heads.

## Next-token prediction

The autoregressive training objective of predicting token \(t_i\) from earlier tokens \(t_{<i}\).

## Non-contextual embedding

The initial vocabulary embedding selected by token ID before sequence interactions change the representation.

## Normalization

A transformation such as LayerNorm or RMSNorm that controls the scale/statistics of hidden activations and helps stabilize deep networks.

## Parameter

A learned numerical value in the model: embedding entries, projection matrices, MLP weights, normalization scales, router weights, and so on.

## Positional information

Any mechanism that makes token order or relative distance available to the model. Examples include learned absolute embeddings, sinusoidal encodings, RoPE, and attention biases.

## Prefill

The inference phase that processes the existing prompt/context and constructs the hidden/attention state needed before autoregressive decode begins.

## Q / K / V — Query, Key, Value

Learned projections used by attention. Queries express what a position is looking for; keys determine how strongly positions match; values contain the information that is mixed when a match is strong.

## Quantization

Representing model weights and/or activations with reduced numerical precision or compressed codebooks to reduce memory, bandwidth, and often compute cost, at some risk of approximation error.

## RAG — Retrieval-Augmented Generation

A system that retrieves relevant external information and places it into the model's usable context before or during generation. It changes the information supplied at inference time rather than directly changing the model weights.

## Residual connection

An additive skip connection that updates a representation as \(x\leftarrow x+f(x)\) rather than replacing it outright.

## Residual stream

The sequence of hidden vectors carried through the transformer stack and incrementally updated by attention and MLP sublayers.

## RLHF — Reinforcement Learning from Human Feedback

A family of post-training approaches that derives a preference/reward signal from human feedback and uses it to optimize model behavior, historically often through a reward model followed by reinforcement learning.

## RoPE — Rotary Positional Embedding

A positional method that rotates query/key coordinates by position-dependent angles. Their dot products then encode relative positional relationships without adding a separate absolute position vector to the residual stream.

## Sampling

Choosing from a probability distribution rather than always taking the maximum-probability token.

## Scaling law

An empirical relationship describing how model loss or capability trends with changes in model size, data, compute, or related resources over a regime.

## SFT — Supervised Fine-Tuning

Training a pretrained model on curated input/output examples to increase the likelihood of desired responses or task behavior.

## Softmax

A transformation from logits to a normalized probability distribution:

\[
p_i=\frac{e^{z_i}}{\sum_j e^{z_j}}
\]

## Token

A discrete unit produced by a tokenizer. It may be a word, subword, punctuation fragment, whitespace-attached piece, byte-derived piece, emoji, or other symbol.

## Token ID

An arbitrary integer index identifying one entry in the tokenizer/model vocabulary. Numeric closeness between IDs has no semantic meaning.

## Tokenizer

The deterministic encoding/decoding system that maps between text and vocabulary tokens/IDs according to a fixed vocabulary and segmentation rules.

## Transformer block

A repeated model unit that updates the residual stream, typically through normalization, self-attention, residual addition, an MLP, and another residual addition, with architectural variants.

## Unigram tokenizer

A subword tokenizer family that maintains candidate pieces with scores/probabilities and chooses a likely segmentation rather than deriving encoding solely from an ordered merge list.

## Vocabulary

The fixed set of token pieces and special symbols understood by a tokenizer/model pair.

## Weight tying

Sharing the same or related weight matrix between input embeddings and the output vocabulary projection.

## World model

A learned model of state and dynamics designed to predict how an environment evolves in a representation useful for prediction, planning, or control. It may operate in a latent space rather than directly predicting raw observations.
