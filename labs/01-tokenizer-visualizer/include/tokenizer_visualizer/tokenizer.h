#pragma once

#include <string>

#include "token_types.h"

namespace tokenizer_visualizer {

class Tokenizer {
 public:
  virtual ~Tokenizer() = default;
  virtual TokenizationResult Tokenize(const std::string& input, const std::string& language) const = 0;
};

}  // namespace tokenizer_visualizer
