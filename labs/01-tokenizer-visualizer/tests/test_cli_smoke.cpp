#include <catch2/catch_test_macros.hpp>

#include "tokenizer_visualizer/cli.h"

TEST_CASE("CLI returns error without input") {
  const char* argv[] = {"tokenizer_visualizer", "--model", "bpe", "--lang", "en"};
  REQUIRE(tokenizer_visualizer::RunCli(5, const_cast<char**>(argv)) == 1);
}
