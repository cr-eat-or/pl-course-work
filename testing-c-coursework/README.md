Курсовая работа по тестированию, отладке и поиску уязвимостей в программе на языке C с применением ИИ.

Проект намеренно содержит ошибки разных классов.

## Требования

- Linux или WSL2;
- GCC 11+ и Clang 14+;
- CMake 3.20+;
- gcovr, cppcheck, clang-tools, Valgrind;
- Mull для мутационного тестирования.

```bash
sudo apt install build-essential cmake clang clang-tools cppcheck valgrind python3-pip
python3 -m pip install gcovr
```

## Сборка и тесты

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
./build/unishop_cli
```

## Санитайзеры

```bash
cmake -S . -B build-san -DENABLE_SANITIZERS=ON -DCMAKE_C_COMPILER=clang
cmake --build build-san
ASAN_OPTIONS=detect_leaks=1 UBSAN_OPTIONS=halt_on_error=1 \
  ctest --test-dir build-san --output-on-failure
```

## Coverage

```bash
cmake -S . -B build-cov -DENABLE_COVERAGE=ON -DCMAKE_C_COMPILER=gcc
cmake --build build-cov
ctest --test-dir build-cov
mkdir -p coverage
gcovr -r . build-cov --html-details coverage/index.html --txt \
  --exclude 'tests/' --branches
```

## Статический и динамический анализ

```bash
cppcheck --enable=warning,style,performance,portability --inconclusive \
  --error-exitcode=1 -Iinclude src
scan-build --status-bugs cmake --build build
valgrind --leak-check=full --show-leak-kinds=all \
  --track-origins=yes --error-exitcode=1 ./build/unishop_tests
```

## Fuzzing

```bash
cmake -S . -B build-fuzz -DBUILD_TESTING=OFF -DBUILD_FUZZERS=ON \
  -DCMAKE_C_COMPILER=clang
cmake --build build-fuzz
mkdir -p corpus
./build-fuzz/fuzz_import corpus -max_total_time=60
```

## Состав

- `include/unishop/`, `src/` — исходный код программы;
- `tests/` — минимальный test harness и smoke-тесты;
- `fuzz/` — стартовая fuzzing-цель.

Проект запускать только в изолированной среде без реальных данных, секретов и повышенных привилегий.
