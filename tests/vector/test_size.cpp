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

TEST_CASE("Vector Size", "[vector.linear]")
{
    auto vector = cwr::vector<double>(10);
    REQUIRE(vector.capacity() == 10);
    REQUIRE(vector.size() == 0);

    vector.push_back(1.3);
    REQUIRE(vector.capacity() == 10);
    REQUIRE(vector.size() == 1);

    for (auto i = 0; i < 20; i++) vector.push_back(i);

    REQUIRE(vector.capacity() == 21);
    REQUIRE(vector.size() == 21);
    REQUIRE(vector.capacity() == vector.size());
}
