#include <catch2/catch_test_macros.hpp>

#include "tokenizer_visualizer/bpe_tokenizer.h"

TEST_CASE("BPE examples match expected output") {
  std::unordered_map<std::string, int> vocab{{"[UNK]",0},{" ",1},{".",2},{",",3},{"!",4},{"¡",5},{"=",6},{";",7},{"x",8},{"42",9},{"Hello",10},{"world",11},{"Hola",12},{"acción",13},{"int",14}};
  std::vector<std::pair<std::string,std::string>> merges{{"H","e"},{"He","l"},{"Hel","l"},{"Hell","o"},{"w","o"},{"wo","r"},{"wor","l"},{"worl","d"},{"H","o"},{"Ho","l"},{"Hol","a"},{"a","c"},{"ac","c"},{"acc","i"},{"acci","ó"},{"acció","n"},{"4","2"},{"i","n"},{"in","t"}};
  tokenizer_visualizer::BPETokenizer tok(vocab, merges);
  auto en = tok.Tokenize("Hello world.", "en");
  REQUIRE(en.tokens == std::vector<std::string>{"Hello"," ","world","."});
  REQUIRE(en.token_ids == std::vector<int>{10,1,11,2});

  auto es = tok.Tokenize("¡Hola, acción!", "es");
  REQUIRE(es.tokens == std::vector<std::string>{"¡","Hola",","," ","acción","!"});
  REQUIRE(es.token_ids == std::vector<int>{5,12,3,1,13,4});

  auto code = tok.Tokenize("int x = 42;", "code");
  REQUIRE(code.tokens == std::vector<std::string>{"int"," ","x"," ","="," ","42",";"});
  REQUIRE(code.token_ids == std::vector<int>{14,1,8,1,6,1,9,7});
}
