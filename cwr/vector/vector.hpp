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
        /**************
         * Constructors
         */

        [[nodiscard]] vector() noexcept : _capacity(0), _size(0), _data(nullptr) { }

        [[nodiscard]] explicit vector(uint64_t capacity) noexcept
            : _capacity(0), _size(0), _data(nullptr)
        {
            _ensure_capacity(capacity);
        }

        // Copy Constructor
        vector(const vector &rhs) noexcept
        {
            _size     = rhs._size;
            _capacity = rhs._capacity;
            _data     = std::make_unique<T[]>(_capacity);
        }

        // Move Constructor
        vector(vector &&rhs) noexcept
            : _size(rhs._size), _capacity(rhs._capacity)
        {
            std::swap(_data, rhs._data);
        }

        /*******************
         * Assignments
         */

        // Copy Assignment
        vector<T> &operator=(const vector<T> &rhs)
        {
            _size     = rhs._size;
            _capacity = rhs._capacity;
            _data     = std::make_unique<T[]>(_capacity);
            std::memcpy(_data, rhs._data, sizeof(T) * _size);
        }

        // Move assignment
        vector<T> &operator=(vector<T> &&rhs) noexcept
          {
              std::swap(_size, rhs._size);
              std::swap(_capacity, rhs._capacity);
              std::swap(_data, rhs._data);
          }

        /****************
         * Element Access
         */

        [[nodiscard]] auto at(uint64_t index) const noexcept
        {
            if (index < _size) return nullptr;
            return _data.get() + index;
        }

        [[nodiscard]] const T &operator[](uint64_t index) const noexcept { return _data[index]; }

        [[nodiscard]] const T &front() const noexcept { return _data[0]; }

        [[nodiscard]] const T &back() const noexcept { return _data[_size - 1]; }

        [[nodiscard]] auto data() const noexcept { return _data.get(); }

        /**********
         * Capacity
         */

        [[nodiscard]] auto empty() const noexcept { return _size == 0; }

        [[nodiscard]] auto size() const noexcept { return _size; }

        [[nodiscard]] constexpr auto max_size() const noexcept { return uint64_t(-1); }

        void reserve(uint64_t capacity) noexcept
        {
            if (!_has_capacity(capacity)) _ensure_capacity(capacity);
        }

        [[nodiscard]] auto capacity() const noexcept { return _capacity; }

        void shrink_to_fit() noexcept
        {
            if (!(_data == nullptr || _size == 0))
            {
                auto new_data = std::make_unique<T[]>(_size);
                std::memmove(new_data, _data, _size * sizeof(T));
                _data.swap(new_data);
                _capacity = _size;
            }
        }

        /***********
         * Modifiers
         */

        void clear() noexcept
        {
            for (auto i = 0; i < _size; i++) _data[i].~T();
            _size = 0;
        }

        void pop_back() noexcept { _data[--_size].~T(); }

        void push_back(const T &value) noexcept
        {
            if (!_has_capacity(_size + 1)) _ensure_capacity(_size + 1);
            _data[_size++] = value;
        }

        template<typename... Args>
        void emplace_back(Args &&... args) noexcept
        {
            if (!_has_capacity(_size + 1)) _ensure_capacity(_size + 1);
            _data.get()[_size++] = std::move(T(std::forward<Args>(args)...));
        }

        void resize(uint64_t size, const T &value = T())
        {
            clear();
            auto new_data = std::make_unique<T[]>(size);
            _data.swap(new_data);
            _capacity = size;
            _size     = size;
            for (auto i = 0; i < size; i++) _data[i] = value;
        }

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
                if (!(_data == nullptr || empty()))
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
