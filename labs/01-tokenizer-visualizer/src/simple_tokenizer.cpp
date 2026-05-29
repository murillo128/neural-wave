#include "tokenizer_visualizer/simple_tokenizer.h"

#include <cctype>

#include "tokenizer_visualizer/utf8_utils.h"

namespace tokenizer_visualizer {

SimpleTokenizer::SimpleTokenizer(std::unordered_map<std::string, int> vocab) : vocab_(std::move(vocab)) {}

TokenizationResult SimpleTokenizer::Tokenize(const std::string& input, const std::string& language) const {
  TokenizationResult out;
  out.original_text = input;
  out.language = language;

  if (input.empty()) return out;

  const auto cps = SplitUtf8Codepoints(input);
  std::string current;
  auto flush_word = [&]() {
    if (current.empty()) return;
    out.tokens.push_back(current);
    auto it = vocab_.find(current);
    out.token_ids.push_back(it == vocab_.end() ? 0 : it->second);
    current.clear();
  };

  for (const auto& cp : cps) {
    if (cp == " " || cp == "." || cp == "," || cp == "!" || cp == "¡" || cp == "=" || cp == ";") {
      flush_word();
      out.tokens.push_back(cp);
      auto it = vocab_.find(cp);
      out.token_ids.push_back(it == vocab_.end() ? 0 : it->second);
    } else {
      current += cp;
    }
  }
  flush_word();
  return out;
}

}  // namespace tokenizer_visualizer
