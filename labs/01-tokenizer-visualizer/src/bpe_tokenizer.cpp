#include "tokenizer_visualizer/bpe_tokenizer.h"

#include "tokenizer_visualizer/utf8_utils.h"

namespace tokenizer_visualizer {

BPETokenizer::BPETokenizer(std::unordered_map<std::string, int> vocab,
                           std::vector<std::pair<std::string, std::string>> merges)
    : vocab_(std::move(vocab)), merges_(std::move(merges)) {}

TokenizationResult BPETokenizer::Tokenize(const std::string& input, const std::string& language) const {
  TokenizationResult out;
  out.original_text = input;
  out.language = language;
  if (input.empty()) return out;

  auto pieces = SplitUtf8Codepoints(input);

  // Educational merge pass: apply known merges greedily in listed order.
  for (const auto& merge : merges_) {
    std::vector<std::string> next;
    for (std::size_t i = 0; i < pieces.size();) {
      if (i + 1 < pieces.size() && pieces[i] == merge.first && pieces[i + 1] == merge.second) {
        next.push_back(merge.first + merge.second);
        i += 2;
      } else {
        next.push_back(pieces[i]);
        ++i;
      }
    }
    pieces = std::move(next);
  }

  out.tokens = pieces;
  out.token_ids.reserve(out.tokens.size());
  for (const auto& tok : out.tokens) {
    auto it = vocab_.find(tok);
    out.token_ids.push_back(it == vocab_.end() ? 0 : it->second);
  }
  return out;
}

}  // namespace tokenizer_visualizer
