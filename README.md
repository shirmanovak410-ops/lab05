[![CI](https://github.com/shirmanovak410-ops/lab05/actions/workflows/ci.yml/badge.svg)](https://github.com/shirmanovak410-ops/lab05/actions/workflows/ci.yml)

# lab05

В рамках выполнения данной лабораторной работы мною были выполнены команды из tutorial с некоторыми изменениями:
1) Скопирован репозиторий из lab04:
```bash
$ git clone https://github.com/${GITHUB_USERNAME}/lab04 projects/lab05
Клонирование в «projects/lab05»...
remote: Enumerating objects: 48, done.
remote: Counting objects: 100% (48/48), done.
remote: Compressing objects: 100% (29/29), done.
remote: Total 48 (delta 11), reused 40 (delta 9), pack-reused 0 (from 0)
Получение объектов: 100% (48/48), 12.30 КиБ | 179.00 КиБ/с, готово.
Определение изменений: 100% (11/11), готово.
$ cd projects/lab05
$ git remote remove origin
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab05
```
2) Установлен и закоммичен gtest более актуальной версии, чем предложено в tutorial:
```bash
$ git submodule add https://github.com/google/googletest third-party/gtest
Клонирование в «/home/ksu/shirmanovak410-ops/workspace/projects/lab05/third-party/gtest»...
remote: Enumerating objects: 28627, done.
remote: Counting objects: 100% (64/64), done.
remote: Compressing objects: 100% (48/48), done.
remote: Total 28627 (delta 32), reused 16 (delta 16), pack-reused 28563 (from 2)
Получение объектов: 100% (28627/28627), 13.78 МиБ | 5.29 МиБ/с, готово.
Определение изменений: 100% (21268/21268), готово.

$ cd third-party/gtest && git checkout release-1.15.2 && cd ../..
$ git add third-party/gtest
$ git commit -m"added gtest framework v1.15.2"
[main a01e205] added gtest framework v1.15.2
 2 files changed, 4 insertions(+)
 create mode 100644 .gitmodules
 create mode 160000 third-party/gtest
```

3) К Cmake.txt добавлен фрагмент кода:
```cmake
if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(third-party/gtest)
  file(GLOB \${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
  add_executable(check \${\${PROJECT_NAME}_TEST_SOURCES})
  target_link_libraries(check \${PROJECT_NAME} gtest_main)
  add_test(NAME check COMMAND check)
endif()
```
4) Написан тест:
```cpp
#include <print.hpp>

#include <gtest/gtest.h>

TEST(Print, InFileStream)
{
  std::string filepath = "file.txt";
  std::string text = "hello";
  std::ofstream out{filepath};

  print(text, out);
  out.close();

  std::string result;
  std::ifstream in{filepath};
  in >> result;

  EXPECT_EQ(result, text);
}
```
5) Произведена сборка и запущены тесты (с менее и более подробным выводом):
```bash
$ cmake -H. -B_build -DBUILD_TESTS=ON
CMake Deprecation Warning at CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.10 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value.  Or, use the <min>...<max> syntax
  to tell CMake that the project requires at least <min> but has been updated
  to work with policies introduced by <max> or earlier.


-- The C compiler identification is GNU 14.2.0
-- The CXX compiler identification is GNU 14.2.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE
-- Configuring done (2.6s)
-- Generating done (0.0s)
-- Build files have been written to: /home/ksu/shirmanovak410-ops/workspace/projects/lab05/_build
```
```bash
$ cmake --build _build
[  8%] Building CXX object CMakeFiles/print.dir/sources/print.cpp.o
[ 16%] Linking CXX static library libprint.a
[ 16%] Built target print
[ 25%] Building CXX object third-party/gtest/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
[ 33%] Linking CXX static library libgtest.a
[ 33%] Built target gtest
[ 41%] Building CXX object third-party/gtest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o
[ 50%] Linking CXX static library libgtest_main.a
[ 50%] Built target gtest_main
[ 58%] Building CXX object CMakeFiles/check.dir/tests/test1.cpp.o
[ 66%] Linking CXX executable check
[ 66%] Built target check
[ 75%] Building CXX object third-party/gtest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o
[ 83%] Linking CXX static library libgmock.a
[ 83%] Built target gmock
[ 91%] Building CXX object third-party/gtest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o
[100%] Linking CXX static library libgmock_main.a
[100%] Built target gmock_main
```
```bash
$ cmake --build _build --target test
Running tests...
Test project /home/ksu/shirmanovak410-ops/workspace/projects/lab05/_build
    Start 1: check
1/1 Test #1: check ............................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.01 sec
```
```bash
$ ./_build/check
[==========] Running 2 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 2 tests from PrintTest
[ RUN      ] PrintTest.FileOutput
[       OK ] PrintTest.FileOutput (0 ms)
[ RUN      ] PrintTest.StreamOutput
[       OK ] PrintTest.StreamOutput (0 ms)
[----------] 2 tests from PrintTest (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test case ran. (0 ms total)
[  PASSED  ] 2 tests.
```
```bash
$ cmake --build _build --target test -- ARGS=--verbose
Running tests...
UpdateCTestConfiguration  from :/home/ksu/shirmanovak410-ops/workspace/projects/lab05/_build/DartConfiguration.tcl
UpdateCTestConfiguration  from :/home/ksu/shirmanovak410-ops/workspace/projects/lab05/_build/DartConfiguration.tcl
Test project /home/ksu/shirmanovak410-ops/workspace/projects/lab05/_build
Constructing a list of tests
Done constructing a list of tests
Updating test list for fixtures
Added 0 tests to meet fixture requirements
Checking test dependency graph...
Checking test dependency graph end
test 1
    Start 1: check

1: Test command: /home/ksu/shirmanovak410-ops/workspace/projects/lab05/_build/check
1: Working Directory: /home/ksu/shirmanovak410-ops/workspace/projects/lab05/_build
1: Test timeout computed to be: 10000000
1: [==========] Running 2 tests from 1 test case.
1: [----------] Global test environment set-up.
1: [----------] 2 tests from PrintTest
1: [ RUN      ] PrintTest.FileOutput
1: [       OK ] PrintTest.FileOutput (0 ms)
1: [ RUN      ] PrintTest.StreamOutput
1: [       OK ] PrintTest.StreamOutput (0 ms)
1: [----------] 2 tests from PrintTest (0 ms total)
1:
1: [----------] Global test environment tear-down
1: [==========] 2 tests from 1 test case ran. (1 ms total)
1: [  PASSED  ] 2 tests.
1/1 Test #1: check ............................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.02 sec
```
6) В файл ci.yml дописана часть кода:
```yml
$ cat > .github/workflows/ci.yml << 'EOF'
> name: CI

on:
  push:
    branches: [ main, master ]
  pull_request:
    branches: [ main, master ]

jobs:
  build:
    runs-on: ubuntu-latest

    steps:
    - uses: actions/checkout@v4
      with:
        submodules: true

    - name: Install dependencies
      run: |
        sudo apt-get update
        sudo apt-get install -y cmake g++ libgtest-dev

    - name: Build GoogleTest
      run: |
        cd /usr/src/gtest
        sudo cmake .
        sudo make
        sudo cp lib/*.a /usr/lib

    - name: Configure CMake
      run: cmake -H. -B_build -DBUILD_TESTS=ON

    - name: Build
      run: cmake --build _build

    - name: Run tests
      run: ./_build/check
EOF
```
7) Все изменения закоммичены и запушены.
8) Репозиторий прошёл все тесты (бейдж об этом в начале отчёта).
