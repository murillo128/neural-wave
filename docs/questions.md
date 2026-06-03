# Questions

## 01 - Tokenization

### Answered

- Why are token IDs arbitrary?
- Why are context windows measured in tokens?
- Why can different languages use different token counts?
- What happens when text exceeds the context window?

### Still fuzzy / later

- How do production BPE or byte-level tokenizers really work?

## 02 - Embeddings

### Answered

- Why do we need embeddings instead of passing token IDs directly?
- What is \(x = E[token\_id]\)?
- What does `hidden_size` mean?
- What is cosine similarity?
- What is the `lm_head`?
- What are logits?

### Still fuzzy / later

- Why do embeddings become semantically organized during training?
- Why can multilingual tokens become close?

## 03 - Positional Information

### Answered

- How does the model know order?
- How are \(P(0), P(1), P(2), \ldots\) obtained?
- Why does the shape stay \(T \times hidden\_size\)?
- What happens beyond context?

### Still fuzzy / later

- How does attention use position?
- Why do modern models often use RoPE?

## Current questions for Lesson 04

- What does a transformer block do from the outside?
- How do token vectors become contextual?
- What enters and exits a transformer block?

## Later questions

- What are Q/K/V?
- What exactly is stored in KV cache?
- Why is decode different from prefill?
- How does quantization affect quality?
- How does serving/batching change the cost model?
