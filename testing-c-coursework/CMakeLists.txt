cmake_minimum_required(VERSION 3.20)
project(unishop_bug_lab VERSION 0.2.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_SANITIZERS "Enable ASan and UBSan" OFF)
option(ENABLE_COVERAGE "Enable GCC coverage instrumentation" OFF)
option(BUILD_FUZZERS "Build libFuzzer target with Clang" OFF)

add_library(unishop
    src/product.c
    src/cart.c
    src/pricing.c
    src/auth.c
    src/order.c
    src/storage.c
    src/files.c
)
target_include_directories(unishop PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(unishop PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
target_link_libraries(unishop PUBLIC m)

if(ENABLE_SANITIZERS)
    target_compile_options(unishop PUBLIC -O1 -g -fno-omit-frame-pointer -fsanitize=address,undefined)
    target_link_options(unishop PUBLIC -fsanitize=address,undefined)
endif()

if(ENABLE_COVERAGE)
    target_compile_options(unishop PUBLIC -O0 -g --coverage)
    target_link_options(unishop PUBLIC --coverage)
endif()

add_executable(unishop_cli src/main.c)
target_link_libraries(unishop_cli PRIVATE unishop)

include(CTest)
if(BUILD_TESTING)
    add_executable(unishop_tests tests/test_main.c)
    target_link_libraries(unishop_tests PRIVATE unishop)
    add_test(NAME unishop_tests COMMAND unishop_tests)
endif()

if(BUILD_FUZZERS)
    if(NOT CMAKE_C_COMPILER_ID MATCHES "Clang")
        message(FATAL_ERROR "BUILD_FUZZERS requires Clang")
    endif()
    add_executable(fuzz_import fuzz/fuzz_import.c)
    target_link_libraries(fuzz_import PRIVATE unishop)
    target_compile_options(fuzz_import PRIVATE -g -O1 -fsanitize=fuzzer,address,undefined)
    target_link_options(fuzz_import PRIVATE -fsanitize=fuzzer,address,undefined)
endif()
