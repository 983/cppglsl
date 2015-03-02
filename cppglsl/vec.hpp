#pragma once

#include "swizzler.hpp"
#include "swizzling.hpp"

namespace cppglsl {

// required for vec *= mat operator
template <class T, int M, int N>
struct mat;

#define V1_VEC_OP(op, N) \
template <int I> vec& operator op (const swizzler<T, N, I> &a){\
    T tmp[N];\
    for (int i = 0; i < N; i++) tmp[i] = a[i];\
    for (int i = 0; i < N; i++) (*this)[i] op tmp[i];\
    return *this;\
}

#define VEC_PARENT(N) swizzler<T, N, V1_ENCODE4_5(0, 1, 2, 3, 0)>

#define VEC_COMMON(member, N) \
union {\
    T data[N];\
    member\
};\
\
vec(){}\
\
explicit vec(const T &a){\
    for (int i = 0; i < N; i++) data[i] = a;\
}\
\
                 vec             (const      vec<T, N   > &a): VEC_PARENT(N)() { V1_SAFE_COPY(a, *this, tmp, N) }\
                 vec& operator = (const      vec<T, N   > &a)                  { V1_SAFE_COPY(a, *this, tmp, N) return *this; }\
template <int I> vec             (const swizzler<T, N, I> &a): VEC_PARENT(N)() { V1_SAFE_COPY(a, *this, tmp, N) }\
template <int I> vec& operator = (const swizzler<T, N, I> &a)                  { V1_SAFE_COPY(a, *this, tmp, N) return *this; }\
\
vec& operator += (T a){ for (int i = 0; i < N; i++) (*this)[i] += a; return *this; }\
vec& operator -= (T a){ for (int i = 0; i < N; i++) (*this)[i] -= a; return *this; }\
vec& operator *= (T a){ for (int i = 0; i < N; i++) (*this)[i] *= a; return *this; }\
vec& operator /= (T a){ for (int i = 0; i < N; i++) (*this)[i] /= a; return *this; }\
\
V1_VEC_OP(+=, N)\
V1_VEC_OP(-=, N)\
V1_VEC_OP(*=, N)\
V1_VEC_OP(/=, N)\
vec operator *= (const mat<T, N, N> &a);

template <class T, int N>
struct vec : VEC_PARENT(N) {
    VEC_COMMON(, N)
};

template <class T>
struct vec <T, 1> : VEC_PARENT(1) {
    VEC_COMMON(
        struct { T x; };,
        1
    )

    explicit vec(const T &x, const T &y): data{x, y}{}
};

template <class T>
struct vec <T, 2> : VEC_PARENT(2) {
    VEC_COMMON(
        struct { T x; T y; };
        struct { T r; T g; };
        struct { T s; T t; };
        V1_VEC2_SWIZZLE,
        2
    )

    explicit vec(const T &x, const T &y): data{x, y}{}
};

template <class T>
struct vec <T, 3> : VEC_PARENT(3) {
    VEC_COMMON(
        struct { T x; T y; T z; };
        struct { T r; T g; T b; };
        struct { T s; T t; T p; };
        V1_VEC3_SWIZZLE,
        3
    )

    explicit vec(const T &x, const T &y, const T &z): data{x, y, z}{}
    template <int I> explicit vec(const swizzler<T, 2, I> &a, const T &z): data{a[0], a[1], z   }{}
    template <int I> explicit vec(const T &x, const swizzler<T, 2, I> &a): data{x   , a[0], a[1]}{}
};

template <class T>
struct vec <T, 4> : VEC_PARENT(4) {
    VEC_COMMON(
        struct { T x; T y; T z; T w; };
        struct { T r; T g; T b; T a; };
        struct { T s; T t; T p; T q; };
        V1_VEC4_SWIZZLE,
        4
    )

    explicit vec(const T &x, const T &y, const T &z, const T &w): data{x, y, z, w}{}

    template <int I       > explicit vec(const swizzler<T, 2, I> &a, const T &z, const T &w    ): data{a[0], a[1], z   , w   }{}
    template <int I       > explicit vec(const T &x, const swizzler<T, 2, I> &a, const T &w    ): data{x   , a[0], a[1], w   }{}
    template <int I       > explicit vec(const T &x, const T &y    , const swizzler<T, 2, I> &a): data{x   , y   , a[0], a[1]}{}
    template <int I, int J> explicit vec(const swizzler<T, 2, I> &a, const swizzler<T, 2, J> &b): data{a[0], a[1], b[0], b[1]}{}
    template <int I       > explicit vec(const swizzler<T, 3, I> &a, const T &w                ): data{a[0], a[1], a[2], w   }{}
    template <int I       > explicit vec(const T &x, const swizzler<T, 3, I> &a                ): data{x   , a[0], a[1], a[2]}{}
};

static_assert(sizeof(vec<int, 2>) == sizeof(int[2]), "vec2 takes more space than it should");
static_assert(sizeof(vec<int, 3>) == sizeof(int[3]), "vec3 takes more space than it should");
static_assert(sizeof(vec<int, 4>) == sizeof(int[4]), "vec4 takes more space than it should");

#define V1_VEC_VEC_OP(op) \
template <class T, int N, int I, int J> \
vec<T, N> operator op (const swizzler<T, N, I> &a, const swizzler<T, N, J> &b){ \
    vec<T, N> c; \
    for (int i = 0; i < N; i++) c[i] = a[i] op b[i]; \
    return c; \
}

#define V1_VEC_SCALAR_OP(op) \
template <class T, int N, int I> \
vec<T, N> operator op (const swizzler<T, N, I> &a, const T &b){ \
    vec<T, N> c; \
    for (int i = 0; i < N; i++) c[i] = a[i] op b; \
    return c; \
}

#define V1_SCALAR_VEC_OP(op) \
template <class T, int N, int J> \
vec<T, N> operator op (const T &a, const swizzler<T, N, J> &b){ \
    vec<T, N> c; \
    for (int i = 0; i < N; i++) c[i] = a op b[i]; \
    return c; \
}

V1_VEC_VEC_OP(+)
V1_VEC_VEC_OP(-)
V1_VEC_VEC_OP(*)
V1_VEC_VEC_OP(/)

V1_VEC_SCALAR_OP(+)
V1_VEC_SCALAR_OP(-)
V1_VEC_SCALAR_OP(*)
V1_VEC_SCALAR_OP(/)

V1_SCALAR_VEC_OP(+)
V1_SCALAR_VEC_OP(-)
V1_SCALAR_VEC_OP(*)

template <class T, int N, int I>
vec<T, N> operator - (const swizzler<T, N, I> &a){
    vec<T, N> c;
    for (int i = 0; i < N; i++) c[i] = -a[i];
    return c;
}

}

