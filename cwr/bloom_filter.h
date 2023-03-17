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

#ifndef CWR_BLOOM_FILTER_H
#define CWR_BLOOM_FILTER_H

#include <cstdint>
#include <vector>
#include <bitset>
#include <functional>
#include "hash.h"

namespace cwr
{
    template <typename T, size_t ByteCount>
    class bloom_filter {
    private:
        std::bitset<ByteCount * 8> bits = {};
        std::function<std::vector<std::byte>(T)> view_bytes;

    public:
        bloom_filter(std::function<std::vector<std::byte>(T)> view_bytes) : view_bytes(std::move(view_bytes)) {};

        void add(T val) {
            auto data = view_bytes(val);
            const auto hash = cwr::hash<cwr::hash_algorithm::murmur64A, ByteCount>(std::span<std::byte>(data));
            for (size_t i = 0; i < ByteCount; i++) {
                const auto byte = hash[i];
                for (size_t j = 0; j < 8; j++) {
                    bits.set(i * 8 + j, bits.test(i * 8 + j) || bool((byte >> j) & std::byte(0x1)));
                }
            }
        }

        [[nodiscard]] bool exists(T val) {
            auto data = view_bytes(val);
            const auto hash = cwr::hash<cwr::hash_algorithm::murmur64A, ByteCount>(std::span<std::byte>(data));
            for (size_t i = 0; i < ByteCount; i++) {
                const auto byte = hash[i];
                for (size_t j = 0; j < 8; j++) {
                    const auto bit = bits.test(i * 8 + j);
                    if (bit == false && bool((byte >> j) & std::byte(0x1))) {
                        return false;
                    }
                }
            }
            return true;
        }

        [[nodiscard]] size_t bit_count() const noexcept { return bits.size(); }
    };
}

#endif    // CWR_BLOOM_FILTER_H
