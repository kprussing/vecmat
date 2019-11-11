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
#include <stdexcept>

int main(void)
{
    static const int N = 3;
    static const int M = 4;
    int success = EXIT_SUCCESS;
    vecmat::matrix<N, M, size_t> a {{ 0,  1,  2,
                                      3,  4,  5,
                                      6,  7,  8,
                                      9, 10, 11}};
    for (size_t i = 0; i < N * M; ++i)
        if (i != a[i])
        {
            std::cout << "size_t " << i << " " << a[i] << std::endl;
            success = EXIT_FAILURE;
        }

    size_t k = 0;
    for (size_t j = 0; j < M; ++j)
        for (size_t i = 0; i < N; ++i)
            if (a(i, j) != k++)
            {
                std::cout << "Element " << i << ", " << j << " was "
                    << a(i, j) << " and not " << k << std::endl;
                success = EXIT_FAILURE;
            }

    for (size_t i = N; i < 100; i += N)
    {
        try
        {
            a[i];
        }
        catch (const std::out_of_range &)
        {
            // This is what should happen
        }
        catch (const std::exception & err)
        {
            std::cout << err.what() << std::endl;
            success = EXIT_FAILURE;
        }
    }

    try
    {
        a(1, 200);
    }
    catch (const std::out_of_range &)
    {
        // This is expected
    }
    catch (const std::exception & err)
    {
        std::cout << err.what() << std::endl;
        success = EXIT_FAILURE;
    }

    return success;
}
