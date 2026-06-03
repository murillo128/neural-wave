# QUESTIONS

Track active learning questions, answered questions, and hypotheses by lesson.

## 01 Tokenization

Answered in Lesson 01:

- Why are token IDs arbitrary?
- Why do token IDs have no semantic meaning by themselves?
- What happens if the input text exceeds the context window?
- Why can two tokenizers produce different token counts for the same text?
- Why do cost, latency, and context usage depend on token count?

Still useful to revisit later:

- How do production tokenizers differ from the tiny educational tokenizer lab?
- How do token budgets shape prompt and chunk design in larger applications?

## 02 Embeddings

Answered in Lesson 02:

- Why do we need embeddings instead of passing token ID numbers directly?
- What is `x = E[token_id]`?
- What does `hidden_size` mean?
- What is cosine similarity?
- What is the `lm_head`?
- What are logits?
- Why does output vocabulary size affect final projection and softmax cost?

Still useful to revisit later:

- Why can embeddings encode semantic similarity?
- Why can words in different languages end up close in embedding space?
- How are embedding vectors learned during training?
- When and why are embedding weights tied to the output projection?

## 03 Positional Information

Answered in Lesson 03:

- How does the model know token order?
- Why are `dog bites man` and `man bites dog` different if the token embeddings are the same but reordered?
- What does positional information add to token embeddings?
- How are `P(0)`, `P(1)`, `P(2)`, ... represented in a learned absolute-position setup?
- Why does the shape remain `T x hidden_size` after adding position?

Still useful to revisit later:

- Why do absolute positional embeddings have long-context limitations?
- Why does RoPE help long-context models?

## Current questions for Lesson 04

- How does an initial token+position vector become contextual?
- What does a transformer block do from the outside?
- How do tokens start to depend on other tokens?
- What stays the same about the `T x hidden_size` shape across a block?
- What should be understood before introducing Q/K/V?

## Later questions

- What exactly is stored in KV cache?
- What is the difference between prefill and decode in the autoregressive loop?
- Why is decode often experienced differently from prefill?
- How does attention use position?
- How does RoPE work mathematically?
- How do long-context extensions work?
- How does quantization affect quality?
- Why do providers differ if models are similar?
- How do training, fine-tuning, RLHF/DPO, RAG, and serving fit into the larger system?

## Experiment log template

- Date:
- Question:
- Hypothesis:
- Experiment:
- Observation:
- Conclusion:
