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
#include "vecmat/vector.hpp"

#include <cstdlib>
#include <iostream>

int main(void)
{
    vecmat::matrix<3, 3, float> a {{2.0, 9.0, 4.0,
                                    7.0, 5.0, 3.0,
                                    6.0, 1.0, 8.0}};
    vecmat::matrix<3, 3, float> b {{1.0, 0.0, 0.0,
                                    0.0, 2.0, 0.0,
                                    0.0, 0.0, 3.0}};

    vecmat::matrix<3, 3, float> c = vecmat::dot(a, b);
    vecmat::matrix<3, 3, float> d1 = {{ 2.0,  9.0,  4.0,
                                       14.0, 10.0,  6.0,
                                       18.0,  3.0, 24.0}};
    int success = EXIT_SUCCESS;
    if (c != d1)
    {
        std::cout << "Matrix multiplication 1 failed!" << std::endl;
        success = EXIT_FAILURE;
    }

    c = vecmat::dot(b, a);
    vecmat::matrix<3, 3, float> d2 = {{ 2.0, 18.0, 12.0,
                                        7.0, 10.0,  9.0,
                                        6.0,  2.0, 24.0}};
    if (c != d2)
    {
        std::cout << "Matrix multiplication 2 failed!" << std::endl;
        success = EXIT_FAILURE;
    }

    vecmat::vector<3, float> v {{1.0, 2.0, 3.0}};
    vecmat::vector<3, float> e = vecmat::dot(a, v);
    vecmat::vector<3, float> e1 {{34, 22, 34}};
    if (e1 != e)
    {
        std::cout << "Matrix-vector multiplication failed! [" 
            << e << "]" << std::endl;
        success = EXIT_FAILURE;
    }

    e = vecmat::dot(v, a);
    vecmat::vector<3, float> e2 {{32, 26, 32}};
    if (e2 != e)
    {
        std::cout << "Vector-matrix multiplication failed! [" 
            << e << "]" << std::endl;
        success = EXIT_FAILURE;
    }

    vecmat::matrix<3, 5, float> f1 {{ 1.0,  2.0,  3.0,
                                      4.0,  5.0,  6.0,
                                      7.0,  8.0,  9.0,
                                     10.0, 11.0, 12.0,
                                     13.0, 14.0, 15.0}};
    vecmat::matrix<3, 5, float> f2 = vecmat::dot(a, f1);
    vecmat::matrix<3, 5, float> f3 {{ 34.0,  22.0,  34.0,
                                      79.0,  67.0,  79.0,
                                     124.0, 112.0, 124.0,
                                     169.0, 157.0, 169.0,
                                     214.0, 202.0, 214.0}};
    if (f3 != f2)
    {
        std::cout << "3x3 time 3x5 failed!" << std::endl;
        success = EXIT_FAILURE;
    }

    vecmat::matrix<5, 3, float> g1 {{ 1.0,  2.0,  3.0,  4.0,  5.0,
                                      6.0,  7.0,  8.0,  9.0, 10.0,
                                     11.0, 12.0, 13.0, 14.0, 15.0}};
    vecmat::matrix<5, 3, float> g2 = vecmat::dot(g1, a);
    vecmat::matrix<5, 3, float> g3 {{100.0, 115.0, 130.0, 145.0, 160.0,
                                      70.0,  85.0, 100.0, 115.0, 130.0,
                                     100.0, 115.0, 130.0, 145.0, 160.0}};
    if (g3 != g2)
    {
        std::cout << "5x3 time 3x3 failed!" << std::endl;
        success = EXIT_FAILURE;
    }

    return success;
}
