Yet Another Vector-Matrix Library
=================================

As the title says, this is just another vector/matrix library for
numerical calculations in C++.  The impetus for this library stemmed
from my dissatisfaction with the current barrage of vector/matrix
libraries.  If the library was not a toy program without sanity checks,
it was too specialized to $R^3$, relied on non-standard compiler
behavior, or had a non-standard Open Source license.  Thus, I wrote my
own with tests and a means to simply install.

My end goal is to have light weight wrapper around a C “array” (which
are just pointers and not _real_ arrays (I'm a Fortran programmer)) that
understands the usual mathematical operations and interoperates with
OpenGL calls.  This means two primary things.  First, all of the common
mathematical operations must be transparently supported.  This includes
addition, subtraction, multiplication, and division with scalars,
vectors, and matrices.  The scalars should broadcast element-wise as in
Fortran.  Second, the underlying data must be tightly packed.

The advantage of needing interoperability with OpenGL is the arrays must
be in column major order.  This buys us the same ordering as Fortran
and, therefore, access to the usual `BLAS` libraries.

This library is a header only library that provides a mathematical
`vector` and `matrix` template class for C++.  The dimensions and types
are template parameters so that an arbitrary length vector or sized
matrix may be used.  The library also provides specializations for
$R^2$, $R^3$, and $R^4$ via the templates `vec2`, `vec3`, and `vec4`
respectively.

Installation
------------

The library can be installed by simply placing the headers in the
include directory on your compiler’s search path.  Alternatively, you
can use [CMake](https://cmake.org) to install the library using

    $ mkdir build
    $ cd build
    $ cmake ..
    # make install

You can run the tests using

    $ make test

You can disable building the tests using

    $ cmake -DENABLE_TESTS:BOOL=Off ..

Usage
-----

Using the library is as simple as including the headers and declaring
your vector

    #include "vecmat/vector.hpp"
    #include "vecmat/matrix.hpp"

    ...

    vecmat::vector<3, float> xhat {{1.0, 0.0, 0.0}};
    vecmat::vector<3, float> yhat {{0.0, 1.0, 0.0}};
    vecmat::vec3<float> zhat = vecmat::cross(xhat, yhat);

    vecmat::matrix<3, 3, float> M {{1.0, 2.0, 3.0,
                                    4.0, 5.0, 6.0,
                                    7.0, 8.0, 9.0}};

    vecmat::vector<3, float> c = 1.1 * xhat + 2.8 * yhat + 4.4 * zhat;
    vecmat::vector<3, float> d = vecmat::dot(M, c);

    ...

Note the vector and matrix use the aggregate style initialization.
Further, the elements of the matrix are stored in column-major order.
This means the matrix in the above is stored as

    M =
    \begin{pmatrix}
        1.0 & 4.0 & 7.0 \\
        2.0 & 5.0 & 8.0 \\
        3.0 & 6.0 & 9.0
    \end{pmatrix}.

A major underlying assumption is the type contained in the vectors and
matrices are real numeric types.  Complex numbers are not considered and
non-numeric types do not make sense mathematically.  The elements are
stored in a C array named `data` that can be passed to functions that
need a pointer to contiguous column major data.  Although the data may
be accessed directly, the usual `[i]` operator is provided for
abstracting away the access.  Additionally, the `(i)` operator access
the elements on the vector and a symmetric `(i, j)` operator access the
`i`-th row and `j`-th column of a matrix.

License
-------

This work is licensed under the 3-clause BSD license.

