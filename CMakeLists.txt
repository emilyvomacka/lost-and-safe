cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(LostAndSafe)

add_executable(LostAndSafe lost_and_safe.cpp database.cpp storage_item.cpp index_item.cpp)

# find_package(Catch2 3 REQUIRED)
# These tests can use the Catch2-provided main
# add_executable(tests tests/storage_tests.cpp)
# target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
