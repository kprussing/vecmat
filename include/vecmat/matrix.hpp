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

#ifndef VECMAT_MATRIX_H
#define VECMAT_MATRIX_H

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>

#include "vecmat/vector.hpp"

namespace vecmat {

template <size_t N, size_t M, typename T>
struct matrix {
    /** A generic matrix for mathematical operations
     *
     * The basic concept is to wrap up a fixed size array as a type that
     * can behave like a mathematical matrix.  The expectation is to use
     * with the provided methods to simply act like a mathematical
     * matrix.  The data are stored tightly packed so that it may
     * interoperate with a standard C array.
     *
     * As the object is just an aggregate, we rely on aggregate
     * initialization to handle zeroing out excess locations in the
     * matrix and brace initialization.  This means the following are
     * equivalent
     *
     *     matrix<2, 2, int> a {}
     *     matrix<2, 2, int> b {{0, 0, 0, 0}};
     *
     * The implicit assumption behind all of these methods are that the
     * internal data type is real and numeric.  No type checking is done
     * before applying the standard mathematical operators to the data.
     */

    /** ## Member data
     */
    T data[N * M];      //! The internal storage for the array

    /** ## Type definitions
     */
    typedef T  type_t;         //! The base type of the matrix
    typedef T* iterator;       //! The iterator across the data
    typedef T* const_iterator; //! The iterator across the constant data

    /** ## Iterator access
     *
     * The standard named access to the iterators for forward traversing
     * the data.  We don't provide a reverse iterator at the moment
     * because we primarily care about forward traversal across the
     * entire data of the matrix.
     */
    iterator begin(void)
    {
        return data;
    }
    iterator end(void)
    {
        return data + N * M;
    }
    const_iterator cbegin(void) const
    {
        return const_cast<const_iterator>(data);
    }
    const_iterator cend(void) const
    {
        return const_cast<const_iterator>(data + N * M);
    }

    /** ## Access operations
     *
     * We provide the usual `[i]` zero based access operator, but we
     * also provide `(i)` for symmetry with the matrix class.  These
     * will throw std::out_of_range if the index is larger than the
     * matrix.
     */
    const T & operator[](const size_t & i) const
    {
        if (i >= N * M)
            std::out_of_range(__func__);
        return data[i];
    }
    T & operator[](const size_t & i)
    {
        if (i >= N * M)
            std::out_of_range(__func__);
        return data[i];
    }
    const T & operator()(const size_t & i, const size_t & j) const
    {
        size_t k = i + j * N;
        return operator[](k);
    }
    T & operator()(const size_t & i, const size_t & j)
    {
        size_t k = i + j * N;
        return operator[](k);
    }

    /** ## Unary operator
     *
     * Negating a matrix negates each element of the matrix.
     */
    matrix operator-()
    {
        matrix<N, M, T> b;
        for (size_t i = 0; i < N * M; ++i)
            b[i] = -operator[](i);

        return b;
    }

    /** Scalar assignment
     *
     * Scalar assignment broadcasts the scalar to every element of the
     * matrix.
     */
    matrix operator=(T a)
    {
        for (auto & x: *this)
            x = a;
        return *this;
    }

    /** ## Compound assignment
     *
     * We have two forms of compound assignment for the basic
     * mathematical operators: scalar/matrix and matrix/matrix.
     * Mathematically, a scalar broadcasts across the entire matrix.
     * For the matrix/matrix, we define the operation in the Fortran
     * sense and do it piecewise.
     */
    /** ### Scalar compound assignment
     */
    matrix & operator+=(const T & a)
    {
        for (auto & v: *this)
            v += a;
        return *this;
    }
    matrix & operator-=(const T & a)
    {
        for (auto & v: *this)
            v -= a;
        return *this;
    }
    matrix & operator*=(const T & a)
    {
        for (auto & v: *this)
            v *= a;
        return *this;
    }
    matrix & operator/=(const T & a)
    {
        for (auto & v: *this)
            v /= a;
        return *this;
    }

    /** ### Matrix compound assignments
     */
    matrix & operator+=(const matrix & a)
    {
        std::transform(a.cbegin(), a.cend(), begin(), begin(),
                       [](T s, T t) -> T { return t + s; });
        return *this;
    }
    matrix & operator-=(const matrix & a)
    {
        std::transform(a.cbegin(), a.cend(), begin(), begin(),
                       [](T s, T t) -> T { return t - s; });
        return *this;
    }
    matrix & operator*=(const matrix & a)
    {
        std::transform(a.cbegin(), a.cend(), begin(), begin(),
                       [](T s, T t) -> T { return t * s; });
        return *this;
    }
    matrix & operator/=(const matrix & a)
    {
        std::transform(a.cbegin(), a.cend(), begin(), begin(),
                       [](T s, T t) -> T { return t / s; });
        return *this;
    }


    /** ## Stream operations
     *
     * We output as a comma separated list of values.  On the reverse,
     * we parse as a (potentially) comma separated list.
     */
    template <size_t O, size_t P, typename U>
    friend std::ostream & operator<<(std::ostream & os,
                                     const matrix<O, P, U> & a);
    template <size_t O, size_t P, typename U>
    friend std::istream & operator>>(std::istream & is,
                                     const matrix<O, P, U> & a);
};

/** ## Binary operators
 *
 * Just like compound assignment, the binary operators need to handle
 * matrix/matrix and scalar/matrix operations.  For the scalar
 * operations, we need to handle the scalar on the left or the scalar on
 * the right.  The only exception is division where dividing a scalar by
 * a matrix does not make sense.  In all cases, we operate element-wise
 * and broadcast the scalars.
 */
/** ### Addition
 */
template <size_t N, size_t M, typename T, typename U>
matrix<N, M, T> operator+(const U & a, matrix<N, M, T> b)
{
    return b += static_cast<T>(a);
}
template <size_t N, size_t M, typename T, typename U>
matrix<N, M, T> operator+(matrix<N, M, T> a, const U & b)
{
    return a += static_cast<T>(b);
}
template <size_t N, size_t M, typename T>
matrix<N, M, T> operator+(matrix<N, M, T> a, const matrix<N, M, T> & b)
{
    return a += b;
}

/** ### Subtraction
 */
template <size_t N, size_t M, typename T, typename U>
matrix<N, M, T> operator-(const U & a, matrix<N, M, T> b)
{
    return (-b) += static_cast<T>(a);
}
template <size_t N, size_t M, typename T, typename U>
matrix<N, M, T> operator-(matrix<N, M, T> a, const U & b)
{
    return a -= static_cast<T>(b);
}
template <size_t N, size_t M, typename T>
matrix<N, M, T> operator-(matrix<N, M, T> a, const matrix<N, M, T> & b)
{
    return a -= b;
}

/** ### Multiplication
 */
template <size_t N, size_t M, typename T, typename U>
matrix<N, M, T> operator*(const U & a, matrix<N, M, T> b)
{
    return b *= static_cast<T>(a);
}
template <size_t N, size_t M, typename T, typename U>
matrix<N, M, T> operator*(matrix<N, M, T> a, const U & b)
{
    return a *= static_cast<T>(b);
}
template <size_t N, size_t M, typename T>
matrix<N, M, T> operator*(matrix<N, M, T> a, const matrix<N, M, T> & b)
{
    return a *= b;
}

/** ### Division
 */
template <size_t N, size_t M, typename T, typename U>
matrix<N, M, T> operator/(matrix<N, M, T> a, const U & b)
{
    return a /= static_cast<T>(b);
}
template <size_t N, size_t M, typename T>
matrix<N, M, T> operator/(matrix<N, M, T> a, const matrix<N, M, T> & b)
{
    return a /= b;
}

/** ### Comparison operators
 *
 * Two matrices are equal if all elements are equal.  This means
 * matrices of different lengths are never equal.
 */
template <size_t N, size_t M, size_t I, size_t J, typename T>
bool operator==(const matrix<N, M, T> & a, const matrix<I, J, T> & b)
{
    if (N != I || M != J)
        return false;

    for (size_t i = 0; i < N * M; ++i)
        if (a[i] != b[i])
            return false;

    return true;
}
template <size_t N, size_t M, size_t I, size_t J, typename T>
bool operator!=(const matrix<N, M, T> & a, const matrix<I, J, T> & b)
{
    return ! operator==(a, b);
}

/**
 * @brief The inner product
 *
 * We have three forms of the inner product: matrix-matrix,
 * vector-matrix, and matrix-vector.  Note the order of the matrix and
 * vector dictate the order of the multiplication.
 */
template <size_t N, size_t M, size_t O, typename T>
matrix<N, O, T> dot(const matrix<N, M, T> & a, const matrix<M, O, T> & b)
{
    matrix<N, O, T> c {};
    for (size_t o = 0; o < O; ++o)
        for (size_t n = 0; n < N; ++n)
            for (size_t m = 0; m < M; ++m)
                    c(n, o) += a(n, m) * b(m, o);

    return c;
}

template <size_t N, size_t M, typename T>
vector<N, T> dot(const matrix<N, M, T> & a, const vector<M, T> & b)
{
    vector<N, T> c {};
    for (size_t n = 0; n < N; ++n)
        for (size_t m = 0; m < M; ++m)
                c(n) += a(n, m) * b(m);

    return c;
}

template <size_t N, size_t M, typename T>
vector<M, T> dot(const vector<N, T> & a, const matrix<N, M, T> & b)
{
    vector<M, T> c {};
    for (size_t n = 0; n < N; ++n)
        for (size_t m = 0; m < M; ++m)
                c(m) += a(n) * b(n, m);

    return c;
}

/** ## Stream operators
 */
/**
 * Output the matrix as a comma separated list in column major order
 */
template <size_t N, size_t M, typename T>
std::ostream & operator<<(std::ostream & os, const matrix<N, M, T> & a)
{
    if (N <= 0 || M <= 0)
        return os;

    os << a[0];
    for (size_t i = 1; i < N * M; ++i)
        os << ", " << a[i];

    return os;
}

/**
 * Read the matrix as a potentially comma separated list
 *
 * This method ignores all white space between the values.  This
 * includes spaces, new lines, and tabs, and anything else recognized as
 * white space by the stream operators.
 *
 * On error, this puts the stream back to its initial position and
 * places a quiet NaN in every element.
 */
template <size_t N, size_t M, typename T>
std::istream & operator>>(std::istream & is, matrix<N, M, T> & a)
{
    if (N <= 0 || M <= 0)
        return is;

    std::istream::pos_type pos = is.tellg();
    is >> std::ws >> a[0];
    for (size_t i = 1; i < N * M; ++i)
    {
        if (!is.good())
        {
            is.seekg(pos);
            a = std::numeric_limits<T>::quiet_NaN();
            break;
        }
        is >> std::ws;
        char comma = is.get();
        if (!is.good())
        {
            is.seekg(pos);
            a = std::numeric_limits<T>::quiet_NaN();
            break;
        }
        if (comma != ',')
            is.unget();

        is >> std::ws >> a[i];
    }
    return is;
}

/** Resize and cast a matrix
 *
 * To cast a matrix to a different size, we fill the new matrix with
 * zeros and then populate the upper left portion of the new matrix with
 * the contents of the old matrix.  This means if the new matrix is
 * larger than the old matrix, the excess elements are zero.  If the new
 * matrix is smaller, the excess data is dropped.  While resizing, we
 * type cast the content.
 */
template <size_t N, size_t M, typename T, size_t I, size_t J, typename U>
vecmat::matrix<N, M, T> resize_cast(const vecmat::matrix<I, J, U> & a)
{
    vecmat::matrix<N, M, T> b {};
    for (size_t m = 0; m < M; ++m)
        for (size_t n = 0; n < N; ++n)
            b(n, m) = static_cast<T>(n < I & m < J ? a(n, m) : 0);

    return b;
}

/** ## Specializations
 *
 * We provide specializations for matrices representing transformations
 * of real space points.  Specifically, we provide the `mat3`, an
 * \f(R^3\f) transformation, `mat2`, a transformation on a plane in
 * \f(R^3\f), and `mat4`, an \f(R^3\f) transformation in a homogeneous
 * coordinate system.  By definition, these are square matrices.
 */
template <typename T>
using mat2 = matrix<2, 2, T>;

template <typename T>
using mat3 = matrix<3, 3, T>;

template <typename T>
using mat4 = matrix<4, 4, T>;

/** Identity matrix
 */
template <size_t N, typename T>
matrix<N, N, T> eye(void)
{
    matrix<N, N, T> I {};
    for (size_t n = 0; n < N; ++n)
        I(n, n) = static_cast<T>(1);

    return I;
}

}; // end namespace vecmat

#endif
