cmake_minimum_required(VERSION 3.20)
project(tokenizer_visualizer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
  nlohmann_json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_Declare(
  Catch2
  URL https://github.com/catchorg/Catch2/archive/refs/tags/v3.5.4.tar.gz
)
FetchContent_MakeAvailable(nlohmann_json Catch2)

add_library(tokenizer_visualizer_lib
  src/cli.cpp
  src/simple_tokenizer.cpp
  src/bpe_tokenizer.cpp
  src/utf8_utils.cpp
  src/file_utils.cpp
  src/json_io.cpp
)
target_include_directories(tokenizer_visualizer_lib PUBLIC include)
target_link_libraries(tokenizer_visualizer_lib PUBLIC nlohmann_json::nlohmann_json)
if (MSVC)
  target_compile_options(tokenizer_visualizer_lib PRIVATE /W4)
else()
  target_compile_options(tokenizer_visualizer_lib PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(tokenizer_visualizer src/main.cpp)
target_link_libraries(tokenizer_visualizer PRIVATE tokenizer_visualizer_lib)

enable_testing()
add_executable(tokenizer_visualizer_tests
  tests/test_simple_tokenizer.cpp
  tests/test_bpe_tokenizer.cpp
  tests/test_utf8_utils.cpp
  tests/test_cli_smoke.cpp
)
target_link_libraries(tokenizer_visualizer_tests PRIVATE tokenizer_visualizer_lib Catch2::Catch2WithMain)
include(CTest)
include(Catch)
catch_discover_tests(tokenizer_visualizer_tests)
