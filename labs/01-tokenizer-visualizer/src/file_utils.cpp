#include "tokenizer_visualizer/file_utils.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace tokenizer_visualizer {

std::string ReadFileOrThrow(const std::string& path) {
  std::ifstream in(path);
  if (!in) throw std::runtime_error("Could not open file: " + path);
  std::ostringstream buffer;
  buffer << in.rdbuf();
  return buffer.str();
}

std::vector<std::pair<std::string, std::string>> ReadMergesFile(const std::string& path) {
  std::ifstream in(path);
  if (!in) throw std::runtime_error("Could not open merges file: " + path);
  std::vector<std::pair<std::string, std::string>> merges;
  std::string a;
  std::string b;
  while (in >> a >> b) merges.push_back({a, b});
  return merges;
}

}  // namespace tokenizer_visualizer
