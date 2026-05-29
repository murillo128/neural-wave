#include "tokenizer_visualizer/utf8_utils.h"

namespace tokenizer_visualizer {

bool IsUtf8ContinuationByte(const unsigned char c) { return (c & 0xC0U) == 0x80U; }

std::vector<std::string> SplitUtf8Codepoints(const std::string& input) {
  std::vector<std::string> parts;
  for (std::size_t i = 0; i < input.size();) {
    unsigned char lead = static_cast<unsigned char>(input[i]);
    std::size_t len = 1;
    if ((lead & 0x80U) == 0) len = 1;
    else if ((lead & 0xE0U) == 0xC0U) len = 2;
    else if ((lead & 0xF0U) == 0xE0U) len = 3;
    else if ((lead & 0xF8U) == 0xF0U) len = 4;
    if (i + len > input.size()) len = 1;
    parts.push_back(input.substr(i, len));
    i += len;
  }
  return parts;
}

}  // namespace tokenizer_visualizer
