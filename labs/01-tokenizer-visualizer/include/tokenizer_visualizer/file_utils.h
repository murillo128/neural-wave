#pragma once

#include <string>
#include <utility>
#include <vector>

namespace tokenizer_visualizer {

std::string ReadFileOrThrow(const std::string& path);
std::vector<std::pair<std::string, std::string>> ReadMergesFile(const std::string& path);

}  // namespace tokenizer_visualizer
