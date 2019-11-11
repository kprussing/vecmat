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

#ifndef VECMAT_VECTOR_H
#define VECMAT_VECTOR_H

#include <algorithm>
#include <cstdlib>
#include <limits>
#include <stdexcept>
#include <iostream>

namespace vecmat {

template <size_t N, typename T>
struct vector {
    /** A generic vector for mathematical operations
     *
     * The basic concept is to wrap up a fixed size array as a type that
     * can behave like a mathematical vector.  The expectation is to use
     * with the provided methods to simply act like a mathematical
     * vector.  The data are stored tightly packed so that it may
     * interoperate with a standard C array.
     *
     * As the object is just an aggregate, we rely on aggregate
     * initialization to handle zeroing out excess locations in the
     * vector and brace initialization.  This means the following are
     * equivalent
     *
     *     vector<2, int> a {};
     *     vector<2, int> b {{0, 0}};
     *
     * The implicit assumption behind all of these methods are that the
     * internal data type is real and numeric.  No type checking is done
     * before applying the standard mathematical operators to the data.
     */

    /** ## Member data
     */
    T data[N];          //! The internal storage for the array

    /** ## Type definitions
     */
    typedef T  type_t;         //! The base type of the vector
    typedef T* iterator;       //! The iterator across the data
    typedef T* const_iterator; //! The iterator across the constant data

    /** ## Iterator access
     *
     * The standard named access to the iterators for forward traversing
     * the data.  We don't provide a reverse iterator at the moment
     * because we primarily care about forward traversal for
     * mathematical vectors.
     */
    iterator begin(void)
    {
        return data;
    }
    iterator end(void)
    {
        return data + N;
    }
    const_iterator cbegin(void) const
    {
        return const_cast<const_iterator>(data);
    }
    const_iterator cend(void) const
    {
        return const_cast<const_iterator>(data + N);
    }

    /** ## Access operations
     *
     * We provide the usual `[i]` zero based access operator, but we
     * also provide `(i)` for symmetry with the matrix class.  These
     * will throw std::out_of_range if the index is larger than the
     * vector.
     */
    const T & operator[](const size_t & i) const
    {
        if (i >= N)
            std::out_of_range(__func__);
        return data[i];
    }
    T & operator[](const size_t & i)
    {
        if (i >= N)
            std::out_of_range(__func__);
        return data[i];
    }
    const T & operator()(const size_t & i) const
    {
        return operator[](i);
    }
    T & operator()(const size_t & i)
    {
        return operator[](i);
    }

    /** ## Unary operator
     *
     * Negating a vector negates each element of the vector.
     */
    vector operator-()
    {
        vector<N, T> b;
        for (size_t i = 0; i < N; ++i)
            b[i] = -operator[](i);

        return b;
    }

    /** Scalar assignment
     *
     * Scalar assignment broadcasts the scalar to every element of the
     * vector.
     */
    vector operator=(T a)
    {
        for (auto & x: *this)
            x = a;
        return *this;
    }

    /** ## Compound assignment
     *
     * We have two forms of compound assignment for the basic
     * mathematical operators: scalar/vector and vector/vector.
     * Mathematically, a scalar broadcasts across the entire vector.
     * For the vector/vector, we define the operation in the Fortran
     * sense and do it piecewise.
     */
    /** ### Scalar compound assignment
     */
    vector & operator+=(const T & a)
    {
        for (auto & v: *this)
            v += a;
        return *this;
    }
    vector & operator-=(const T & a)
    {
        for (auto & v: *this)
            v -= a;
        return *this;
    }
    vector & operator*=(const T & a)
    {
        for (auto & v: *this)
            v *= a;
        return *this;
    }
    vector & operator/=(const T & a)
    {
        for (auto & v: *this)
            v /= a;
        return *this;
    }

    /** ### Vector compound assignments
     */
    vector & operator+=(const vector & a)
    {
        std::transform(a.cbegin(), a.cend(), begin(), begin(),
                       [](T s, T t) -> T { return t + s; });
        return *this;
    }
    vector & operator-=(const vector & a)
    {
        std::transform(a.cbegin(), a.cend(), begin(), begin(),
                       [](T s, T t) -> T { return t - s; });
        return *this;
    }
    vector & operator*=(const vector & a)
    {
        std::transform(a.cbegin(), a.cend(), begin(), begin(),
                       [](T s, T t) -> T { return t * s; });
        return *this;
    }
    vector & operator/=(const vector & a)
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
    template <size_t M, typename U>
    friend std::ostream & operator<<(std::ostream & os,
                                     const vector<M, U> & a);
    template <size_t M, typename U>
    friend std::istream & operator>>(std::istream & is,
                                     const vector<M, U> & a);
};

/** ## Binary operators
 *
 * Just like compound assignment, the binary operators need to handle
 * vector/vector and scalar/vector operations.  For the scalar
 * operations, we need to handle the scalar on the left or the scalar on
 * the right.  The only exception is division where dividing a scalar by
 * a vector does not make sense.  In all cases, we operate elementwise
 * and broadcast the scalars.
 */
/** ### Addition
 */
template <size_t N, typename T, typename U>
vector<N, T> operator+(const U & a, vector<N, T> b)
{
    return b += static_cast<T>(a);
}
template <size_t N, typename T, typename U>
vector<N, T> operator+(vector<N, T> a, const U & b)
{
    return a += static_cast<T>(b);
}
template <size_t N, typename T>
vector<N, T> operator+(vector<N, T> a, const vector<N, T> & b)
{
    return a += b;
}

/** ### Subtraction
 */
template <size_t N, typename T, typename U>
vector<N, T> operator-(const U & a, vector<N, T> b)
{
    return (-b) += static_cast<T>(a);
}
template <size_t N, typename T, typename U>
vector<N, T> operator-(vector<N, T> a, const U & b)
{
    return a -= static_cast<T>(b);
}
template <size_t N, typename T>
vector<N, T> operator-(vector<N, T> a, const vector<N, T> & b)
{
    return a -= b;
}

/** ### Multiplication
 */
template <size_t N, typename T, typename U>
vector<N, T> operator*(const U & a, vector<N, T> b)
{
    return b *= static_cast<T>(a);
}
template <size_t N, typename T, typename U>
vector<N, T> operator*(vector<N, T> a, const U & b)
{
    return a *= static_cast<T>(b);
}
template <size_t N, typename T>
vector<N, T> operator*(vector<N, T> a, const vector<N, T> & b)
{
    return a *= b;
}

/** ### Division
 */
template <size_t N, typename T, typename U>
vector<N, T> operator/(vector<N, T> a, const U & b)
{
    return a /= static_cast<T>(b);
}
template <size_t N, typename T>
vector<N, T> operator/(vector<N, T> a, const vector<N, T> & b)
{
    return a /= b;
}

/** ### Comparison operators
 *
 * Two vectors are equal if all elements are equal.  This means vectors
 * of different lengths are never equal.
 */
template <size_t N, size_t M, typename T>
bool operator==(const vector<N, T> & a, const vector<M, T> & b)
{
    if (M != N)
        return false;

    for (size_t i = 0; i < N; ++i)
        if (a[i] != b[i])
            return false;

    return true;
}
template <size_t N, size_t M, typename T>
bool operator!=(const vector<N, T> & a, const vector<M, T> & b)
{
    return ! operator==(a, b);
}

/**
 * @brief The inner product
 *
 * The inner product is the sum of the product of the elements, but the
 * convention is to call it the `dot product'
 */
template <size_t N, typename T>
T dot(const vector<N, T> & a, const vector<N, T> & b)
{
    T ret = 0;
    for (size_t i = 0; i < N; i++)
        ret += a[i] * b[i];
    return ret;
}

/** ## Stream operators
 */
/**
 * Output the vector as a comma separated list
 */
template <size_t N, typename T>
std::ostream & operator<<(std::ostream & os, const vector<N, T> & a)
{
    if (N <= 0)
        return os;

    os << a[0];
    for (size_t i = 1; i < N; ++i)
        os << ", " << a[i];

    return os;
}

/**
 * Read the vector as a potentially comma separated list
 *
 * This method ignores all white space between the values.  This
 * includes spaces, new lines, and tabs, and anything else recognized as
 * white space by the stream operators.
 *
 * On error, this puts the stream back to its initial position and
 * places a quiet NaN in every element.
 */
template <size_t N, typename T>
std::istream & operator>>(std::istream & is, vector<N, T> & a)
{
    if (N <= 0)
        return is;

    std::istream::pos_type pos = is.tellg();
    is >> std::ws >> a[0];
    for (size_t i = 1; i < N; ++i)
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

/** ## \f(R^3\f) specific detail
 *
 * A simple application of a numeric vector is the representation of
 * position in \f(R^3\f).  For these vectors, we define specializations.
 * Additionally, we provide symbolic means to access the elements.
 */

/** ## Specializations
 *
 * We provide specializations for vectors representing real space
 * points.  Specifically, we provide the `vec3`, an \f(R^3\f) point,
 * `vec2`, a point on a plane in \f(R^3\f), and `vec4`, an \f(R^3\f)
 * vector in a homogeneous coordinate system.
 */
template <typename T>
using vec2 = vector<2, T>;

template <typename T>
using vec3 = vector<3, T>;

template <typename T>
using vec4 = vector<4, T>;

/** ### Symbolic access
 *
 * We want to access the elements using symbols like `X' or `Y' or `Z'
 * and not have to care about the underlying layout.  We provide
 * homogeneous Cartesian coordinate notation (`W' is the fourth
 * coordinate) along with the RGBA notation that is common in rendering
 * pipelines.
 */
enum coords_t {X=0, Y, Z, W};
enum rgba_t {R=0, G, B, A};

/**
 * @brief The cross product
 *
 * The cross product is only defined in \f(R^3\f).  However, a vector in
 * \f(R^2\f) can implicitly be upcast to \f(R^3\f) by assuming they are
 * the \f(x\f) and \f(y\f).  On the other hand, a vector in a
 * homogeneous coordinate system can be down cast to the embedded
 * \f(R^3\f) coordinate system.  If the length of either vector is not
 * between 2 and 4, this throws std::out_of_range.
 */
template <size_t N, size_t M, typename T>
vector<3, T> cross(const vector<N, T> & a, const vector<M, T> & b)
{
    if (N < 2 || 4 < N || M < 2 || 4 < M)
        throw std::out_of_range(__func__);

    vector<3, T> c {};
    c[X] = a[Y] * (M > 2 ? b[Z] : 0) - (N > 2 ? a[Z] : 0) * b[Y];
    c[Y] = (M > 2 ? a[Z] : 0) * b[X] - a[X] * (N > 2 ? b[Z] : 0);
    c[Z] = a[X] * b[Y] - a[Y] * b[X];
    return c;
}

/** Resize and cast a vector
 *
 * To cast a vector to a different size, we fill the new vector with
 * zeros and then populate the first portion of the new vector with
 * the contents of the old vector.  This means if the new vector is
 * longer than the old vector, the excess elements are zero.  If the
 * new vector is smaller, the excess data is dropped.  While we're at
 * it, we can type cast the contents.
 */
template <size_t N, typename T, size_t M, typename U>
vecmat::vector<N, T> resize_cast(const vecmat::vector<M, U> & a)
{
    vecmat::vector<N, T> b {};
    for (size_t i = 0; i < N; ++i)
        b[i] = static_cast<T>(i < M ? a[i] : 0);

    return b;
}

}; // end namespace vecmat

#endif
