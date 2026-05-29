#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "tokenizer.h"

namespace tokenizer_visualizer {

class BPETokenizer final : public Tokenizer {
 public:
  BPETokenizer(std::unordered_map<std::string, int> vocab,
               std::vector<std::pair<std::string, std::string>> merges);
  TokenizationResult Tokenize(const std::string& input, const std::string& language) const override;

 private:
  std::unordered_map<std::string, int> vocab_;
  std::vector<std::pair<std::string, std::string>> merges_;
};

}  // namespace tokenizer_visualizer
