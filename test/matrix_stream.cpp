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
#include <sstream>
#include <string>

template <size_t N, size_t M, typename T>
int checkit(void)
{
    vecmat::matrix<N, M, T> a {};
    for (size_t i = 0; i < N * M; ++i)
        a[i] = static_cast<T>(i);

    std::stringstream ss;
    ss << a;
    vecmat::matrix<N, M, T> b {};
    ss.seekg(0);
    ss >> b;
    int success = EXIT_SUCCESS;
    for (size_t i = 0; i < N * M; ++i)
        if (a[i] != b[i])
            success = EXIT_FAILURE;

    return success;
}

int main(void)
{
    int success = EXIT_SUCCESS;
    if (checkit<4, 5, int>() != EXIT_SUCCESS)
    {
        std::cout << "int 4 does not match" << std::endl;
        success = EXIT_FAILURE;
    }

    if (checkit<4, 3, float>() != EXIT_SUCCESS)
    {
        std::cout << "float 4 does not match" << std::endl;
        success = EXIT_FAILURE;
    }

    vecmat::matrix<3, 2, int> a {};

    std::stringstream ss("1 2 3 4 5 6");
    ss >> a;
    for (int i = 0; i < 6; ++i)
        if (a[i] != i + 1)
        {
            std::cout << "No commas " << i << " " << a[i] << std::endl;
            success = EXIT_FAILURE;
        }

    ss.str("1, 2 3 4 5 6");
    ss.seekg(0);
    ss >> a;
    for (int i = 0; i < 6; ++i)
        if (a[i] != i + 1)
        {
            std::cout << "One comma " << i << " " << a[i] << std::endl;
            success = EXIT_FAILURE;
        }

    ss.str("1    2  ,       3,\t4,    5   6");
    ss.seekg(0);
    ss >> a;
    for (int i = 0; i < 6; ++i)
        if (a[i] != i + 1)
        {
            std::cout << "Many spaces " << i << " " << a[i] << std::endl;
            success = EXIT_FAILURE;
        }

    ss.str("\n1\t,  \n2\n\n\n,\t\t\t\t3\n\n,\n\n4 5,\t\t\t6");
    ss.seekg(0);
    ss >> a;
    for (int i = 0; i < 6; ++i)
        if (a[i] != i + 1)
        {
            std::cout << "White space " << i << " " << a[i] << std::endl;
            success = EXIT_FAILURE;
        }

    return success;
}
