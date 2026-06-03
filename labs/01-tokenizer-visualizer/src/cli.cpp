#include "tokenizer_visualizer/cli.h"

#include <filesystem>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

#include "tokenizer_visualizer/bpe_tokenizer.h"
#include "tokenizer_visualizer/file_utils.h"
#include "tokenizer_visualizer/json_io.h"
#include "tokenizer_visualizer/simple_tokenizer.h"
#include "tokenizer_visualizer/token_types.h"
#include "tokenizer_visualizer/tokenizer.h"

namespace tokenizer_visualizer {
namespace {

void PrintHelp() {
  std::cerr << "Usage: tokenizer_visualizer --model <simple|bpe|tiktoken|path> [--text ...|--input-file ...] --lang <en|es|code> [--top-n N]\n";
}

}  // namespace

int RunCli(int argc, char** argv) {
  std::string model = "bpe";
  std::string text;
  std::string input_file;
  std::string lang = "en";
  int top_n = 5;

  for (int i = 1; i < argc; ++i) {
    const std::string arg = argv[i];
    if ((arg == "--model" || arg == "--text" || arg == "--input-file" || arg == "--lang" || arg == "--top-n") && i + 1 >= argc) {
      PrintHelp();
      return 1;
    }
    if (arg == "--model") model = argv[++i];
    else if (arg == "--text") text = argv[++i];
    else if (arg == "--input-file") input_file = argv[++i];
    else if (arg == "--lang") lang = argv[++i];
    else if (arg == "--top-n") top_n = std::stoi(argv[++i]);
    else if (arg == "--help" || arg == "-h") { PrintHelp(); return 0; }
  }

  if (!text.empty() && !input_file.empty()) {
    std::cerr << "Error: --text and --input-file are mutually exclusive.\n";
    return 1;
  }
  if (text.empty() && input_file.empty()) {
    PrintHelp();
    return 1;
  }
  if (!input_file.empty()) {
    if (!std::filesystem::exists(input_file)) {
      std::cerr << "Error: input file does not exist: " << input_file << "\n";
      return 1;
    }
    text = ReadFileOrThrow(input_file);
    if (!text.empty() && text.back() == '\n') text.pop_back();
  }

  const std::string default_vocab = "data/tiny_vocab.json";
  const std::string default_merges = "data/tiny_merges.txt";
  auto vocab = ReadVocabJson(default_vocab);
  auto merges = ReadMergesFile(default_merges);

  std::size_t vocab_size = vocab.size();
  std::unique_ptr<Tokenizer> tokenizer;
  if (model == "simple") tokenizer = std::make_unique<SimpleTokenizer>(vocab);
  else if (model == "bpe") tokenizer = std::make_unique<BPETokenizer>(vocab, merges);
  else if (model == "tiktoken") {
    std::cerr << "Warning: tiktoken mode maps to educational BPE in this lab.\n";
    tokenizer = std::make_unique<BPETokenizer>(vocab, merges);
  } else {
    auto custom_vocab = ReadVocabJson(model);
    vocab_size = custom_vocab.size();
    tokenizer = std::make_unique<SimpleTokenizer>(std::move(custom_vocab));
  }

  auto result = tokenizer->Tokenize(text, lang);

  std::cout << "vocab_size=" << vocab_size << '\n';
  std::cout << "Token table\n-----------\n";
  for (std::size_t i = 0; i < result.tokens.size(); ++i) {
    std::cout << std::setw(3) << i << " | " << std::setw(12) << result.tokens[i] << " | " << result.token_ids[i] << '\n';
  }
  std::cout << "token_count=" << result.token_count() << " chars_per_token=" << std::fixed << std::setprecision(2)
            << result.chars_per_token() << " language=" << result.language << '\n';
  std::cout << "top_n=" << top_n << " (educational placeholder for frequency views)\n";

  if (result.token_count() > kEducationalContextLimit) {
    std::cerr << "Warning: token count " << result.token_count()
              << " exceeds educational context limit " << kEducationalContextLimit << ".\n";
  }

  WriteOutputJson(result, "output.json");
  std::cout << "Wrote output.json\n";
  return 0;
}

}  // namespace tokenizer_visualizer
