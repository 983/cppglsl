#pragma once

#include "vec.hpp"

namespace cppglsl {

#define V1_MAT_COMMON(M, N) \
vec<T, M> cols[N];\
mat(){}\
      vec<T, M>& operator [] (int i)       { return cols[i]; }\
const vec<T, M>& operator [] (int i) const { return cols[i]; }\

template <class T, int M, int N>
struct mat {
    V1_MAT_COMMON(M, N)
};

template <class T>
struct mat <T, 2, 2> {
    V1_MAT_COMMON(2, 2)

    mat(
        const T &m00, const T &m10,
        const T &m01, const T &m11
    ){
        cols[0][0] = m00; cols[1][0] = m01;
        cols[0][1] = m10; cols[1][1] = m11;
    }

    mat(
        const vec<T, 2> &a,
        const vec<T, 2> &b
    ){
        cols[0] = a;
        cols[1] = b;
    }
};

template <class T>
struct mat <T, 3, 3> {
    V1_MAT_COMMON(3, 3)

    mat(
        const T &m00, const T &m10, const T &m20,
        const T &m01, const T &m11, const T &m21,
        const T &m02, const T &m12, const T &m22
    ){
        cols[0][0] = m00; cols[1][0] = m01; cols[2][0] = m02;
        cols[0][1] = m10; cols[1][1] = m11; cols[2][1] = m12;
        cols[0][2] = m20; cols[1][2] = m21; cols[2][2] = m22;
    }

    mat(
        const vec<T, 3> &a,
        const vec<T, 3> &b,
        const vec<T, 3> &c
    ){
        cols[0] = a;
        cols[1] = b;
        cols[2] = c;
    }
};

template <class T>
struct mat <T, 4, 4> {

    V1_MAT_COMMON(4, 4)
    mat(
        const T &m00, const T &m10, const T &m20, const T &m30,
        const T &m01, const T &m11, const T &m21, const T &m31,
        const T &m02, const T &m12, const T &m22, const T &m32,
        const T &m03, const T &m13, const T &m23, const T &m33
    ){
        cols[0][0] = m00; cols[1][0] = m01; cols[2][0] = m02; cols[3][0] = m03;
        cols[0][1] = m10; cols[1][1] = m11; cols[2][1] = m12; cols[3][1] = m13;
        cols[0][2] = m20; cols[1][2] = m21; cols[2][2] = m22; cols[3][2] = m23;
        cols[0][3] = m30; cols[1][3] = m31; cols[2][3] = m32; cols[3][3] = m33;
    }

    mat(
        const vec<T, 4> &a,
        const vec<T, 4> &b,
        const vec<T, 4> &c,
        const vec<T, 4> &d
    ){
        cols[0] = a;
        cols[1] = b;
        cols[2] = c;
        cols[3] = d;
    }
};

template <class T, int N, int I>
vec<T, N> operator * (const swizzler<T, N, I> &a, const mat<T, N, N> &b){
    vec<T, N> c;
    for (int i = 0; i < N; i++){
        T sum(0);
        for (int j = 0; j < N; j++) sum += a[j] * b[i][j];
        c[i] = sum;
    }
    return c;
}

template <class T, int N, int I>
vec<T, N> operator * (const mat<T, N, N> &a, const swizzler<T, N, I> &b){
    vec<T, N> c;
    for (int i = 0; i < N; i++){
        T sum(0);
        for (int j = 0; j < N; j++) sum += a[j][i] * b[j];
        c[i] = sum;
    }
    return c;
}

template <class T, int M, int N, int K>
mat<T, M, N> operator * (const mat<T, M, K> &a, const mat<T, K, N> &b){
    mat<T, M, N> c;
    for (int i = 0; i < M; i++) for (int j = 0; j < N; j++){
        T sum(0);
        for (int k = 0; k < K; k++){
            sum += a[k][i] * b[j][k];
        }
        c[j][i] = sum;
    }
    return c;
}

template <class T, int M, int N>
mat<T, N, M> transpose(const mat<T, M, N> &a){
    mat<T, N, M> c;
    for (int i = 0; i < M; i++) for (int j = 0; j < N; j++){
        c[i][j] = a[j][i];
    }
    return c;
}

template <class T, int M, int N>
bool operator == (const mat<T, M, N> &a, const mat<T, M, N> &b){
    for (int i = 0; i < M; i++) for (int j = 0; j < N; j++){
        if (a[i][j] != b[i][j]) return false;
    }
    return true;
}

template <class T, int M, int N>
bool operator != (const mat<T, M, N> &a, const mat<T, M, N> &b){
    return !(a == b);
}

#define VEC_MUL_MAT(N) \
template <class T>\
vec<T, N> vec<T, N>::operator *= (const mat<T, N, N> &b){\
    T tmp[N];\
    vec<T, N> &a = *this;\
    for (int i = 0; i < N; i++) tmp[i] = a[i];\
\
    for (int i = 0; i < N; i++){\
        T sum(0);\
        for (int j = 0; j < N; j++) sum += tmp[j] * b[i][j];\
        a[i] = sum;\
    }\
}

VEC_MUL_MAT(2)
VEC_MUL_MAT(3)
VEC_MUL_MAT(4)

}
