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

/*
 * I can't figure out how this test is very useful, but I guess if we try to optimize things
 * having something that should be trivial tested, and keeping a 100% code coverage
 * is a good idea. So this is staying
 */
TEST_CASE("Vector Emplace", "[vector.linear]")
{
    class Test
    {
    public:
        int a;
        double b;
        Test(int a, double b) : a(a), b(b) { }
    };

    auto vector = cwr::vector<Test>();
    vector.emplace_back(1, 3.5847);
    vector.emplace_back(8, 6.9420);

    REQUIRE(vector[0].a == 1);
    REQUIRE(vector[0].b == 3.5847);
    REQUIRE(vector[1].a == 8);
    REQUIRE(vector[1].b == 6.9420);
}
