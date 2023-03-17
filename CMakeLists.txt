cmake_minimum_required(VERSION 3.16)
project(cwr)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

set(CMAKE_CXX_STANDARD 20)

set(LIBRARY_HEADERS
        cwr/vector/vector.hpp
        )

add_executable(tests
        tests/bloom_filter.cpp
        tests/hash.cpp)

target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)