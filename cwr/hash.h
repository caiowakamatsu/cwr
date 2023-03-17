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

#ifndef CWR_HASH_H
#define CWR_HASH_H

#include <array>
#include <span>

namespace cwr {
    namespace hash_algorithm {
        namespace detail {
            template <typename T>
            class byte_range {
            public:
                template <typename U>
                class iterator {
                private:
                    std::byte *ptr;
                    size_t count;
                    size_t current;
                public:
                    iterator(std::byte *ptr, size_t count, size_t current = 0) : ptr(ptr), count(count), current(current) {}

                    [[nodiscard]] U operator*() const {
                        auto val = U();
                        const auto to_copy = std::min(sizeof(T), count - current);
                        std::memcpy(&val, ptr, to_copy);
                        return val;
                    }

                    [[nodiscard]] U* operator->() = delete;

                    [[nodiscard]] iterator<U>& operator++() {
                        ptr += sizeof(U);
                        current += sizeof(U);
                        return *this;
                    }

                    [[nodiscard]] iterator<U> operator++(int) {
                        auto tmp = *this;
                        ++(*this);
                        return tmp;
                    }

                    [[nodiscard]] friend bool operator==(const iterator<U> &a, const iterator<U> &b) {
                        return a.ptr == b.ptr;
                    }

                    [[nodiscard]] friend bool operator!=(const iterator<U> &a, const iterator<U> &b) {
                        return a.ptr != b.ptr;
                    }
                };
            private:
                std::span<std::byte> view;

            public:
                explicit byte_range(std::span<std::byte> view) : view(view) {}

                [[nodiscard]] iterator<T> begin() { return iterator<T>(view.data(), view.size()); }
                [[nodiscard]] iterator<T> end() {
                    const auto past = (view.size() / sizeof(T) + 1) * sizeof(T);
                    return iterator<T>(view.data() + past, view.size());
                }

            };
        }

        struct md5 {
            using ReturnType = std::array<std::byte, 128>;
            static ReturnType hash(std::span<std::byte> bytes) {

            }
        };

        struct murmur64A {
            using ReturnType = std::array<std::byte, 64>;
            static ReturnType hash(std::span<std::byte> bytes) {
                const auto m = uint64_t(0xc6a4a7935bd1e995LLU);
                const auto r = int32_t(47);
                const auto h = uint64_t(0x47E9D158EA7D4C05LLU) ^ (bytes.size() * m);

                for (auto byte : detail::byte_range<uint64_t>(bytes)) {
                    
                }
            }
        };
    }

    template <typename Algorithm, size_t OutN, typename T>
    [[nodiscard]] std::array<std::byte, OutN> hash(T &val) {
        auto source = std::array<std::byte, sizeof(T)>();
        auto out = std::array<std::byte, OutN>();

        std::memcpy(source.data(), &val, sizeof(T));



        return out;
    }
}

#endif    // CWR_HASH_H
