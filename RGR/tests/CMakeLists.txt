cmake_minimum_required(VERSION 3.10)
project(Tests)

enable_testing()
find_package(cmocka REQUIRED)

add_executable(tests test_main.c test_polybius.c)

target_link_libraries(tests cmocka)
add_test(NAME Tests COMMAND tests)
set(CTEST_OUTPUT_ON_FAILURE ON)