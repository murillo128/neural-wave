#include "tokenizer_visualizer/json_io.h"

#include <fstream>
#include <stdexcept>

#include <nlohmann/json.hpp>

namespace tokenizer_visualizer {

std::unordered_map<std::string, int> ReadVocabJson(const std::string& path) {
  std::ifstream in(path);
  if (!in) throw std::runtime_error("Could not open vocab json: " + path);
  nlohmann::json j;
  in >> j;
  return j.get<std::unordered_map<std::string, int>>();
}

void WriteOutputJson(const TokenizationResult& result, const std::string& output_path) {
  nlohmann::json j;
  j["original_text"] = result.original_text;
  j["tokens"] = result.tokens;
  j["token_ids"] = result.token_ids;
  j["token_count"] = result.token_count();
  j["chars_per_token"] = result.chars_per_token();
  j["language"] = result.language;

  std::ofstream out(output_path);
  if (!out) throw std::runtime_error("Could not write output json: " + output_path);
  out << j.dump(2) << '\n';
}

}  // namespace tokenizer_visualizer
