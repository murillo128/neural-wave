#pragma once

#include <string>
#include <vector>

namespace tokenizer_visualizer {

bool IsUtf8ContinuationByte(unsigned char c);
std::vector<std::string> SplitUtf8Codepoints(const std::string& input);

}  // namespace tokenizer_visualizer
