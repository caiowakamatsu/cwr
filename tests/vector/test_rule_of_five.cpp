/*
Copyright (c) 2021

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <catch2/catch.hpp>

#include <cwr/vector/vector.hpp>

TEST_CASE("Vector rule of five", "[vector.linear]")
{
    auto odd_numbers = cwr::vector<int>();
    odd_numbers.reserve(10);
    for (auto i = 1; i < 10 * 2; i += 2) odd_numbers.push_back(i);

    auto even_numbers = cwr::vector<int>();
    even_numbers.reserve(10);
    for (auto i = 0; i < 10 * 2; i += 2) even_numbers.push_back(i);

    auto copy_of_odd_numbers = odd_numbers;
    REQUIRE(copy_of_odd_numbers.data() != odd_numbers.data());
    REQUIRE(copy_of_odd_numbers.size() == odd_numbers.size());
    REQUIRE(copy_of_odd_numbers.capacity() == odd_numbers.capacity());

    auto old_even_data(even_numbers.data());
    auto old_even_size(even_numbers.size());
    auto old_even_capacity(even_numbers.capacity());
    auto moved_even_numbers = std::move(even_numbers);
    REQUIRE(moved_even_numbers.data() == old_even_data);
    REQUIRE(moved_even_numbers.size() == old_even_size);
    REQUIRE(moved_even_numbers.capacity() == old_even_capacity);
}
