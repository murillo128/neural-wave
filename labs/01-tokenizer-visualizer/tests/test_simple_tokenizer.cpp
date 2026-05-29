#include <catch2/catch_test_macros.hpp>

#include "tokenizer_visualizer/simple_tokenizer.h"

TEST_CASE("Simple tokenizer handles empty and punctuation") {
  tokenizer_visualizer::SimpleTokenizer tok({{"[UNK]",0},{" ",1},{".",2},{"Hello",10}});
  auto empty = tok.Tokenize("", "en");
  REQUIRE(empty.tokens.empty());

  auto out = tok.Tokenize("Hello.", "en");
  REQUIRE(out.tokens == std::vector<std::string>{"Hello","."});
  REQUIRE(out.token_ids == std::vector<int>{10,2});
}
