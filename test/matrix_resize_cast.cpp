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
    int success = EXIT_SUCCESS;

    vecmat::matrix<3, 4, int> a {{ 1,  2,  3,
                                   4,  5,  6,
                                   7,  8,  9,
                                  10, 11, 12}};
    vecmat::matrix<3, 3, float> b = vecmat::resize_cast<3, 3, float>(a);
    for (size_t k = 0, j = 0; j < 3; ++j)
        for (size_t i = 0;  i < 3; ++i, ++k)
            if (static_cast<float>(k + 1) != b(i, j))
            {
                success = EXIT_FAILURE;
                std::cout << "Down size casting failed! " << b(i, j)
                    << " versus " << k + 1 << std::endl;
            }

    vecmat::matrix<4, 2, size_t> c = vecmat::resize_cast<4, 2, size_t>(a);
    for (size_t k = 0, j = 0; j < 2; ++j)
        for (size_t i = 0; i < 4; ++i)
            if (i < 3 && j < 4)
            {
                if (++k != c(i, j))
                {
                    success = EXIT_FAILURE;
                    std::cout << "Up size casting failed! c(" << i
                        << ", " << j << ") = " << c(i, j) << " versus "
                        << k << std::endl;
                }
            }
            else if (0 != c(i, j))
            {
                success = EXIT_FAILURE;
                std::cout << "Up size casting failed! c(" << i << ", "
                    << j << ") = " << c(i, j) << " versus " << 0
                    << std::endl;
            }

    return success;
}
