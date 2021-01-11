cmake_minimum_required(VERSION 3.16)
project(cwr)

find_package(Catch2 REQUIRED)

set(CMAKE_CXX_STANDARD 17)

set(LIBRARY_HEADERS

        cwr/vector/vector.hpp
        )

add_executable(tests tests/vector/test_size.cpp tests/main.cpp tests/vector/test_emplace_back.cpp)

target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(tests PRIVATE Catch2::Catch2)