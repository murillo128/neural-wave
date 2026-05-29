#include <catch2/catch_test_macros.hpp>

#include "tokenizer_visualizer/utf8_utils.h"

TEST_CASE("UTF-8 split keeps unicode code points") {
  auto cps = tokenizer_visualizer::SplitUtf8Codepoints("¡acción!");
  REQUIRE(cps.front() == "¡");
  REQUIRE(cps.back() == "!");
}
