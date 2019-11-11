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
    static const size_t N = 5;
    int success = EXIT_SUCCESS;
    typedef vecmat::vector<N, int> avec;
    avec a {{0, 1, 2, 3, 4}};

    std::cout << a << std::endl;
    for (auto v: a)
        std::cout << v << ",";
    std::cout << std::endl;

    size_t i = 0;
    for (avec::iterator it = a.begin(); it != a.end(); ++it, ++i)
        if (a[i] != *it)
            success = EXIT_FAILURE;

    std::cout << i << std::endl;
    success = i == N ? EXIT_SUCCESS : EXIT_FAILURE;

    if (success != EXIT_SUCCESS)
        std::cout << "Forward iterator failed!" << std::endl;

    i = 0;
    for (avec::const_iterator it = a.begin(); it != a.end(); ++it, ++i)
        if (a[i] != *it)
            success = EXIT_FAILURE;

    success = i == N ? EXIT_SUCCESS : EXIT_FAILURE;

    if (success != EXIT_SUCCESS)
        std::cout << "Constant forward iterator failed!" << std::endl;

    return success;
}