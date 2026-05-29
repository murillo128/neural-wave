#pragma once

#include <string>
#include <unordered_map>

#include "token_types.h"

namespace tokenizer_visualizer {

std::unordered_map<std::string, int> ReadVocabJson(const std::string& path);
void WriteOutputJson(const TokenizationResult& result, const std::string& output_path);

}  // namespace tokenizer_visualizer
