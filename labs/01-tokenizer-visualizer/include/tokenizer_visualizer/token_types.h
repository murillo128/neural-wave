#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace tokenizer_visualizer {

constexpr std::size_t kEducationalContextLimit = 32;

struct TokenizationResult {
  std::string original_text;
  std::vector<std::string> tokens;
  std::vector<int> token_ids;
  std::string language;

  std::size_t token_count() const { return tokens.size(); }
  double chars_per_token() const {
    if (tokens.empty()) return 0.0;
    return static_cast<double>(original_text.size()) / static_cast<double>(tokens.size());
  }
};

}  // namespace tokenizer_visualizer
