#pragma once

#include <unordered_map>

#include "tokenizer.h"

namespace tokenizer_visualizer {

class SimpleTokenizer final : public Tokenizer {
 public:
  explicit SimpleTokenizer(std::unordered_map<std::string, int> vocab);
  TokenizationResult Tokenize(const std::string& input, const std::string& language) const override;

 private:
  std::unordered_map<std::string, int> vocab_;
};

}  // namespace tokenizer_visualizer
