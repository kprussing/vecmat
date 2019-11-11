/*
Copyright 2019 Keith F. Prussing

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

1.  Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
2.  Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
3.  Neither the name of the copyright holder nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "vecmat/vector.hpp"

#include <cstdlib>
#include <iostream>

static const int N = 3;

vecmat::vector<N, float> reset(void)
{
    vecmat::vector<N, float> a {{1.0, 2.0, 3.0}};
    return a;
};

int main(void)
{
    int success = EXIT_SUCCESS;
    vecmat::vector<N, float> a {};
    for (auto x: a)
        if (x != 0)
        {
            success = EXIT_FAILURE;
            std::cout << "An initialization value was not 0" << std::endl;
        }

    a -= 1;
    for (auto x: a)
        if (x != -1)
        {
            success = EXIT_FAILURE;
            std::cout << "Scalar subtraction was not -1" << std::endl;
        }

    a += 2;
    for (auto x: a)
        if (x != 1)
        {
            success = EXIT_FAILURE;
            std::cout << "Scalar addition was not 1" << std::endl;
        }

    a *= 4;
    for (auto x: a)
        if (x != 4)
        {
            success = EXIT_FAILURE;
            std::cout << "Scalar multiplication was not 4" << std::endl;
        }

    a /= 2;
    for (auto x: a)
        if (x != 2)
        {
            success = EXIT_FAILURE;
            std::cout << "Scalar division was not 2" << std::endl;
        }

    vecmat::vector<N, float> b = reset();
    a = reset();
    a += b;
    for (size_t i = 1; i <= N; ++i)
        if (a[i-1] != i + i)
        {
            success = EXIT_FAILURE;
            std::cout << "Vector addition was not equal" << std::endl;
        }

    a = reset();
    a -= b;
    for (size_t i = 1; i <= N; ++i)
        if (a[i-1] != i - i)
        {
            success = EXIT_FAILURE;
            std::cout << "Vector subtraction was not equal" << std::endl;
        }

    a = reset();
    a *= b;
    for (size_t i = 1; i <= N; ++i)
        if (a[i-1] != i * i)
        {
            success = EXIT_FAILURE;
            std::cout << "Vector multiplication was not equal" << std::endl;
        }

    a = reset();
    a /= b;
    for (size_t i = 1; i <= N; ++i)
        if (a[i-1] != i / i)
        {
            success = EXIT_FAILURE;
            std::cout << "Vector division was not equal" << std::endl;
        }

    return success;
}
