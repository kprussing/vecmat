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

int main(void)
{
    int success = EXIT_SUCCESS;

    vecmat::vec3<float> xhat {{1.0, 0.0, 0.0}};
    vecmat::vec3<float> yhat {{0.0, 1.0, 0.0}};
    vecmat::vec3<float> zhat {{0.0, 0.0, 1.0}};

    vecmat::vector<3, float> a = vecmat::cross(xhat, yhat);
    if (a != zhat)
    {
        std::cout << "x cross y not equal z! " << a << std::endl;
        success = EXIT_FAILURE;
    }
    a = vecmat::cross(yhat, zhat);
    if (a != xhat)
    {
        std::cout << "y cross z not equal x! " << a << std::endl;
        success = EXIT_FAILURE;
    }
    a = vecmat::cross(zhat, xhat);
    if (a != yhat)
    {
        std::cout << "z cross x not equal y! " << a << std::endl;
        success = EXIT_FAILURE;
    }

    a = vecmat::cross(yhat, xhat);
    if (a != -zhat)
    {
        std::cout << "y cross x not equal -z! " << a << std::endl;
        success = EXIT_FAILURE;
    }
    a = vecmat::cross(zhat, yhat);
    if (a != -xhat)
    {
        std::cout << "z cross y not equal -x! " << a << std::endl;
        success = EXIT_FAILURE;
    }
    a = vecmat::cross(xhat, zhat);
    if (a != -yhat)
    {
        std::cout << "x cross z not equal -y! " << a << std::endl;
        success = EXIT_FAILURE;
    }

    vecmat::vec2<float> xhat2 {{1.0, 0.0}};
    vecmat::vec2<float> yhat2 {{0.0, 1.0}};
    a = vecmat::cross(xhat2, yhat2);
    if (a != zhat)
    {
        std::cout << "R^2: x cross y not equal z! " << a << std::endl;
        success = EXIT_FAILURE;
    }
    a = vecmat::cross(yhat2, xhat2);
    if (a != -zhat)
    {
        std::cout << "R^2: y cross x not equal -z! " << a << std::endl;
        success = EXIT_FAILURE;
    }

    vecmat::vec4<float> xhat4 {{1.0, 0.0, 0.0, 0.0}};
    vecmat::vec4<float> yhat4 {{0.0, 1.0, 0.0, 0.0}};
    vecmat::vec4<float> zhat4 {{0.0, 0.0, 1.0, 0.0}};

    a = vecmat::cross(xhat4, yhat4);
    if (a != zhat)
    {
        std::cout << "R^4: x cross y not equal z! " << a << std::endl;
        success = EXIT_FAILURE;
    }
    a = vecmat::cross(yhat4, zhat4);
    if (a != xhat)
    {
        std::cout << "R^4: y cross z not equal x! " << a << std::endl;
        success = EXIT_FAILURE;
    }
    a = vecmat::cross(zhat4, xhat4);
    if (a != yhat)
    {
        std::cout << "R^4: z cross x not equal y! " << a << std::endl;
        success = EXIT_FAILURE;
    }

    a = vecmat::cross(yhat4, xhat4);
    if (a != -zhat)
    {
        std::cout << "R^4: y cross x not equal -z! " << a << std::endl;
        success = EXIT_FAILURE;
    }
    a = vecmat::cross(zhat4, yhat4);
    if (a != -xhat)
    {
        std::cout << "R^4: z cross y not equal -x! " << a << std::endl;
        success = EXIT_FAILURE;
    }
    a = vecmat::cross(xhat4, zhat4);
    if (a != -yhat)
    {
        std::cout << "R^4: x cross z not equal -y! " << a << std::endl;
        success = EXIT_FAILURE;
    }

    vecmat::vec3<float> null {{0.0, 0.0, 0.0}};
    a = vecmat::cross(xhat, xhat4);
    if (a != null)
    {
        std::cout << "x_3 cross x_4 not null! " << a << std::endl;
        success = EXIT_FAILURE;
    }
    a = vecmat::cross(xhat2, yhat4);
    if (a != zhat)
    {
        std::cout << "x_2 cross x_4 not z_3! " << a << std::endl;
        success = EXIT_FAILURE;
    }

    return success;
}
