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

#pragma once

#include <cstdint>
#include <memory>
#include <cstring>

namespace cwr
{
    template<typename T>
    class vector
    {
    public:
        [[maybe_unused]] [[nodiscard]] vector() noexcept
            : _capacity(0), _size(0), _data(nullptr) { }

        [[maybe_unused]] [[nodiscard]] explicit vector(uint64_t capacity) noexcept
            : _capacity(0), _size(0), _data(nullptr)
        {
            _ensure_capacity(capacity);
        }

        [[maybe_unused]] void reserve(uint64_t capacity) noexcept
        {
            if (!_has_capacity(capacity)) _ensure_capacity(capacity);
        }

        [[maybe_unused]] void push_back(const T &value) noexcept
        {
            if (!_has_capacity(_size + 1)) _ensure_capacity(_size + 1);
            _data.get()[_size++] = value;
        }

        template<typename... Args>
        [[maybe_unused]] void emplace_back(Args &&... args) noexcept
        {
            if (!_has_capacity(_size + 1)) _ensure_capacity(_size + 1);
            _data.get()[_size++] = std::move(T(std::forward<Args>(args)...));
        }

        [[maybe_unused]] [[nodiscard]] const T &operator[](uint64_t index) const noexcept
        {
            return _data[index];
        }

        [[maybe_unused]] [[nodiscard]] auto data() const noexcept { return _data; }

        [[maybe_unused]] [[nodiscard]] auto size() const noexcept { return _size; }

        [[maybe_unused]] [[nodiscard]] auto capacity() const noexcept { return _capacity; }

    private:
        [[nodiscard]] inline auto _has_capacity(uint64_t capacity) const noexcept
        {
            return capacity <= _capacity;
        }

        void _ensure_capacity(uint64_t capacity) noexcept
        {
            if (capacity > _capacity)
            {
                auto new_data = std::make_unique<T[]>(capacity);
                std::memmove(
                  new_data.get(),
                  _data.get(),
                  _size * sizeof(T));    // Todo - Replace with custom implementation
                _data.swap(new_data);
                _capacity = capacity;
            }
        }

        uint64_t             _size;
        uint64_t             _capacity;
        std::unique_ptr<T[]> _data;    // Todo - Replace with custom implementation
    };
}    // namespace cwr
