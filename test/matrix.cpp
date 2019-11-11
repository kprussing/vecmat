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

#include "vecmat/matrix.hpp"

#include <cstdlib>
#include <iostream>

int main(void)
{
    static const int N = 3;
    vecmat::matrix<N, N, int> a {};
    int success = EXIT_SUCCESS;
    for (auto v: a)
        if (v != 0)
            success = EXIT_FAILURE;

    if (success != EXIT_SUCCESS)
        std::cout << "A value was not 0" << std::endl;

    if (sizeof(a) != N * N * sizeof(int))
    {
        success = EXIT_FAILURE;
        std::cout << "sizeof int test failed" << std::endl;
    }

    static const int M = 4;
    vecmat::matrix<N, M, size_t> b {{ 0,  1,  2,
                                      3,  4,  5,
                                      6,  7,  8,
                                      9, 10, 11}};
    for (size_t i = 0; i < N * M; ++i)
        if (i != b[i])
        {
            std::cout << "size_t " << i << " " << b[i] << std::endl;
            success = EXIT_FAILURE;
        }

    if (sizeof(b) != N * M * sizeof(size_t))
    {
        success = EXIT_FAILURE;
        std::cout << "sizeof size_t test failed" << std::endl;
    }

    vecmat::matrix<N, N, float> c {{0.0, 1.0, 2.0,
                                    3.0, 4.0, 5.0,
                                    6.0, 7.0, 8.0}};
    for (size_t i = 0; i < N * N; ++i)
        if (static_cast<float>(i) != c[i])
        {
            std::cout << "float " << i << " " << c[i] << std::endl;
            success = EXIT_FAILURE;
        }

    if (sizeof(c) != N * N * sizeof(float))
    {
        success = EXIT_FAILURE;
        std::cout << "sizeof float test failed" << std::endl;
    }

    return success;
}
