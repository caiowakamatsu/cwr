/*
Copyright (c) 2023
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

#include <string>

#include <catch2/catch_all.hpp>

#include <cwr/bloom_filter.h>

TEST_CASE("adding elements", "[bloom_filter]") {
    auto filter = cwr::bloom_filter<std::string, 53>([](auto str){
                                                         auto bytes = std::vector<std::byte>(str.size());
                                                         std::memcpy(bytes.data(), str.data(), str.size());
                                                         return bytes;
    });
    filter.add(std::string("Hello world!"));
    filter.add(std::string("Hello world!"));
    REQUIRE(filter.exists("boo") == false);
    REQUIRE(filter.exists(std::string("Hello world!")) == true);
    auto c= 5;
}
