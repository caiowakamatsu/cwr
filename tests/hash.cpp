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

#include <cwr/hash.h>

namespace {
    template <typename T> requires std::is_integral_v<T>
    [[nodiscard]] std::pair<std::vector<std::byte>, std::vector<T>> make_test_data(std::vector<int> source) {
        auto byte_source = std::vector<std::byte>(source.size());
        for (size_t i = 0; i < byte_source.size(); i++) {
            byte_source[i] = std::byte(source[i]);
        }

        auto expected = std::vector<T>();
        auto i = size_t(0);
        for (; i < byte_source.size() - sizeof(T); i += sizeof(T)) {
            auto val = T();
            std::memcpy(&val, byte_source.data() + i, sizeof(T));
            expected.push_back(val);
        }

        if (i != byte_source.size()) {
            const auto left_over = byte_source.size() - i;
            auto val = T();
            std::memcpy(&val, byte_source.data() + i, left_over);
            expected.push_back(val);
        }

        return {byte_source, expected };
    }
}

TEST_CASE("byte_range", "[hash]") {
    {
        auto [source, expected] = make_test_data<uint64_t>({0, 1, 2, 3, 4, 5, 6, 8, 30});
        size_t i = 0;
        for (auto value : cwr::hash_algorithm::detail::byte_range<uint64_t>(source)) {
            REQUIRE(value == expected[i++]);
        }
    }
    {
        auto [source, expected] = make_test_data<uint32_t>({0, 1, 2, 3, 4, 5, 6, 8, 30});
        size_t i = 0;
        for (auto value : cwr::hash_algorithm::detail::byte_range<uint32_t>(source)) {
            REQUIRE(value == expected[i++]);
        }
    }
    {
        auto [source, expected] = make_test_data<uint16_t>({0, 1, 2, 3, 4, 5, 6, 8, 30});
        size_t i = 0;
        for (auto value : cwr::hash_algorithm::detail::byte_range<uint16_t>(source)) {
            REQUIRE(value == expected[i++]);
        }
    }
}

TEST_CASE("murmur64A", "[hash]") {
    REQUIRE_NOTHROW(cwr::hash<cwr::hash_algorithm::murmur64A, 53>("Hello World!"));
}
