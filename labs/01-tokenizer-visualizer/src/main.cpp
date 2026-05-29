#include <exception>
#include <iostream>

#include "tokenizer_visualizer/cli.h"

int main(int argc, char** argv) {
  try {
    return tokenizer_visualizer::RunCli(argc, argv);
  } catch (const std::exception& ex) {
    std::cerr << "Fatal error: " << ex.what() << '\n';
    return 1;
  }
}
