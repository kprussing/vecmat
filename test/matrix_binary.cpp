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
    vecmat::matrix<3, 1, float> xhat {{1.0, 0.0, 0.0}};
    vecmat::matrix<3, 1, float> yhat {{0.0, 1.0, 0.0}};
    vecmat::matrix<3, 1, float> zhat {{0.0, 0.0, 1.0}};
    vecmat::matrix<3, 1, float> a {};

    a = 2 + xhat;
    if ( a[0] != 3.0 || a[1] != 2.0 || a[2] != 2.0)
    {
        std::cout << "Left scalar addition failed! " << a << std::endl;
        success = EXIT_FAILURE;
    }
    a = xhat + 2;
    if ( a[0] != 3.0 || a[1] != 2.0 || a[2] != 2.0)
    {
        std::cout << "Right scalar addition failed! " << a << std::endl;
        success = EXIT_FAILURE;
    }
    a = xhat + yhat;
    if ( a[0] != 1.0 || a[1] != 1.0 || a[2] != 0.0)
    {
        std::cout << "Matrix addition failed!" << std::endl;
        success = EXIT_FAILURE;
    }

    a = 5 - zhat;
    if ( a[0] != 5.0 || a[1] != 5.0 || a[2] != 4.0)
    {
        std::cout << "Left scalar subtraction failed! " << a << std::endl;
        success = EXIT_FAILURE;
    }
    a = zhat - 5;
    if ( a[0] != -5.0 || a[1] != -5.0 || a[2] != -4.0)
    {
        std::cout << "Right scalar subtraction failed! " << a << std::endl;
        success = EXIT_FAILURE;
    }
    a = yhat - zhat;
    if ( a[0] != 0.0 || a[1] != 1.0 || a[2] != -1.0)
    {
        std::cout << "Matrix subtraction failed!" << std::endl;
        success = EXIT_FAILURE;
    }

    a = 4 * yhat;
    if ( a[0] != 0.0 || a[1] != 4.0 || a[2] != 0.0)
    {
        std::cout << "Left scalar multiplication failed! " << a << std::endl;
        success = EXIT_FAILURE;
    }
    a = yhat * 4;
    if ( a[0] != 0.0 || a[1] != 4.0 || a[2] != 0.0)
    {
        std::cout << "Right scalar multiplication failed! " << a << std::endl;
        success = EXIT_FAILURE;
    }

    vecmat::matrix<3, 1, float> b {{1.0, 2.0, 3.0}};
    a = b * yhat;
    if ( a[0] != 0.0 || a[1] != 2.0 || a[2] != 0.0)
    {
        std::cout << "Matrix multiplication failed!" << std::endl;
        success = EXIT_FAILURE;
    }

    a = b / 2;
    if ( a[0] != 0.5 || a[1] != 1.0 || a[2] != 1.5)
    {
        std::cout << "Right scalar division failed!" << std::endl;
        success = EXIT_FAILURE;
    }
    a = b / a;
    if ( a[0] != 2.0 || a[1] != 2.0 || a[2] != 2.0)
    {
        std::cout << "Matrix division failed! " << a << std::endl;
        success = EXIT_FAILURE;
    }

    return success;
}
