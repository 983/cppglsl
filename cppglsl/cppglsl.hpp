#pragma once

#include "vec.hpp"
#include "mat.hpp"
#include "sampler.hpp"

#include <cmath>

namespace cppglsl {

#define V1_COMMA ,

typedef vec<double, 2> vec2;
typedef vec<double, 3> vec3;
typedef vec<double, 4> vec4;
typedef mat<double, 2, 2> mat2;
typedef mat<double, 3, 3> mat3;
typedef mat<double, 4, 4> mat4;
typedef sampler<double, 2, 4> sampler2D;

using std::sqrt;
using std::floor;
using std::round;
using std::trunc;
using std::sin;
using std::cos;
using std::tan;
using std::asin;
using std::acos;
using std::atan;
using std::pow;
using std::exp;
using std::log;
using std::exp2;
using std::log2;
using std::atan2;

int    abs(int    a){ return a < 0    ? -a : a; }
float  abs(float  a){ return a < 0.0f ? -a : a; }
double abs(double a){ return a < 0.0  ? -a : a; }

int    min(int    a, int    b){ return a < b ? a : b; }
float  min(float  a, float  b){ return a < b ? a : b; }
double min(double a, double b){ return a < b ? a : b; }

int    max(int    a, int    b){ return a > b ? a : b; }
float  max(float  a, float  b){ return a > b ? a : b; }
double max(double a, double b){ return a > b ? a : b; }

float  atan(float  y, float  x){ return atan2(y, x); }
double atan(double y, double x){ return atan2(y, x); }

float  degrees(float  x){ return x*(180.0f / 3.14159265358979323846f         ); }
double degrees(double x){ return x*(180.0  / 3.14159265358979323846          ); }
float  radians(float  x){ return x*(         3.14159265358979323846f / 180.0f); }
double radians(double x){ return x*(         3.14159265358979323846  / 180.0 ); }

float  mod (float  x, float  y){ return fmod(x, y); }
double mod (double x, double y){ return fmod(x, y); }

int    sign(int    x){ return x < 0    ? -1    : x > 0    ? +1    : 0   ; }
float  sign(float  x){ return x < 0.0f ? -1.0f : x > 0.0f ? +1.0f : 0.0f; }
double sign(double x){ return x < 0.0  ? -1.0  : x > 0.0  ? +1.0  : 0.0 ; }

int    fract(int    a){ return a           ; }
float  fract(float  a){ return a - floor(a); }
double fract(double a){ return a - floor(a); }

float  inversesqrt(float  x){ return 1.0f/sqrt(x); }
double inversesqrt(double x){ return 1.0 /sqrt(x); }

int    clamp(int    x, int    a, int    b){ return max(a, min(b, x)); }
float  clamp(float  x, float  a, float  b){ return max(a, min(b, x)); }
double clamp(double x, double a, double b){ return max(a, min(b, x)); }

float smoothstep(float edge0, float edge1, float x){
    float t = clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
    return t * t * (3.0f - 2.0f * t);
}

double smoothstep(double edge0, double edge1, double x){
    double t = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
    return t * t * (3.0 - 2.0 * t);
}

int    step(int    edge, int    x){ return x < edge ? 0    : 1   ; }
float  step(float  edge, float  x){ return x < edge ? 0.0f : 1.0f; }
double step(double edge, double x){ return x < edge ? 0.0  : 1.0 ; }

float  mix(float  x, float  y, float  a){ return x * (1.0f - a) + y * a; }
double mix(double x, double y, double a){ return x * (1.0  - a) + y * a; }

template <class T, int I, int J>
vec<T, 3> cross(const swizzler<T, 3, I> &x, const swizzler<T, 3, J> &y){
    return vec<T, 3>(
        x[1]*y[2] - y[1]*x[2],
        x[2]*y[0] - y[2]*x[0],
        x[0]*y[1] - y[0]*x[1]
    );
}

#define V1_VEC_VEC_FUNC1(func) \
template <class T, int N, int I>\
vec<T, N> func(const swizzler<T, N, I> &a){\
    vec<T, N> b;\
    for (int i = 0; i < N; i++) b[i] = func(a[i]);\
    return b;\
}

#define V1_VEC_VEC_FUNC2(func) \
template <class T, int N, int I, int J>\
vec<T, N> func(const swizzler<T, N, I> &a, const swizzler<T, N, J> &b){\
    vec<T, N> c;\
    for (int i = 0; i < N; i++) c[i] = func(a[i], b[i]);\
    return c;\
}

#define V1_VEC_SCALAR_FUNC2(func) \
template <class T, int N, int I>\
vec<T, N> func(const swizzler<T, N, I> &a, const T &b){\
    vec<T, N> c;\
    for (int i = 0; i < N; i++) c[i] = func(a[i], b);\
    return c;\
}

#define V1_SCALAR_VEC_FUNC2(func) \
template <class T, int N, int I>\
vec<T, N> func(const T &a, const swizzler<T, N, I> &b){\
    vec<T, N> c;\
    for (int i = 0; i < N; i++) c[i] = func(a, b[i]);\
    return c;\
}

#define V1_VEC_VEC_FUNC3(func) \
template <class T, int N, int I, int J, int K>\
vec<T, N> func(\
    const swizzler<T, N, I> &a,\
    const swizzler<T, N, J> &b,\
    const swizzler<T, N, K> &c){\
    vec<T, N> d;\
    for (int i = 0; i < N; i++) d[i] = func(a[i], b[i], c[i]);\
    return d;\
}

V1_VEC_VEC_FUNC1(degrees)
V1_VEC_VEC_FUNC1(radians)
V1_VEC_VEC_FUNC1(sign)
V1_VEC_VEC_FUNC1(fract)
V1_VEC_VEC_FUNC1(abs)
V1_VEC_VEC_FUNC1(floor)
V1_VEC_VEC_FUNC1(ceil)
V1_VEC_VEC_FUNC1(round)
V1_VEC_VEC_FUNC1(trunc)
V1_VEC_VEC_FUNC1(sin)
V1_VEC_VEC_FUNC1(cos)
V1_VEC_VEC_FUNC1(tan)
V1_VEC_VEC_FUNC1(asin)
V1_VEC_VEC_FUNC1(acos)
V1_VEC_VEC_FUNC1(atan)
V1_VEC_VEC_FUNC1(log)
V1_VEC_VEC_FUNC1(exp)
V1_VEC_VEC_FUNC1(log2)
V1_VEC_VEC_FUNC1(exp2)
V1_VEC_VEC_FUNC1(sqrt)
V1_VEC_VEC_FUNC1(inversesqrt)

V1_VEC_VEC_FUNC2(min)
V1_VEC_VEC_FUNC2(max)
V1_VEC_VEC_FUNC2(mod)
V1_VEC_VEC_FUNC2(pow)
V1_VEC_VEC_FUNC2(step)
V1_VEC_VEC_FUNC2(atan)
V1_VEC_VEC_FUNC2(atan2)

V1_VEC_SCALAR_FUNC2(min)
V1_VEC_SCALAR_FUNC2(max)
V1_VEC_SCALAR_FUNC2(mod)
V1_VEC_SCALAR_FUNC2(pow)
V1_VEC_SCALAR_FUNC2(step)
V1_VEC_SCALAR_FUNC2(atan)
V1_VEC_SCALAR_FUNC2(atan2)

V1_SCALAR_VEC_FUNC2(min)
V1_SCALAR_VEC_FUNC2(max)
V1_SCALAR_VEC_FUNC2(mod)
V1_SCALAR_VEC_FUNC2(pow)
V1_SCALAR_VEC_FUNC2(step)
V1_SCALAR_VEC_FUNC2(atan)
V1_SCALAR_VEC_FUNC2(atan2)

V1_VEC_VEC_FUNC3(mix)
V1_VEC_VEC_FUNC3(clamp)
V1_VEC_VEC_FUNC3(smoothstep)

template <class T, int N, int I, int J>
vec<T, N>  mix(
    const swizzler<T, N, I> &x,
    const swizzler<T, N, J> &y,
    const T &a
){
    vec<T, N>  b;
    for (int i = 0; i < N; i++) b[i] = mix(x[i], y[i], a);
    return b;
}

template <class T, int N, int I>
vec<T, N>  clamp(const swizzler<T, N, I> &x, const T &a, const T &b){
    vec<T, N>  c;
    for (int i = 0; i < N; i++) c[i] = clamp(x[i], a, b);
    return c;
}

template <class T, int N, int I, int J>
T dot(const swizzler<T, N, I> &a, const swizzler<T, N, J> &b){
    T c(0);
    for (int i = 0; i < N; i++) c += a[i] * b[i];
    return c;
}

template <class T, int N, int I>
T length(const swizzler<T, N, I> &a){
    return sqrt(dot(a, a));
}

template <class T, int N, int I, int J>
T distance(const swizzler<T, N, I> &a, const swizzler<T, N, J> &b){
    return length(a - b);
}

template <class T, int N, int I>
vec<T, N> normalize(const swizzler<T, N, I> &a){
    return a * inversesqrt(dot(a, a));
}

template <class T, int N, int I, int J>
vec<T, N> reflect(
    const swizzler<T, N, I> &incident,
    const swizzler<T, N, J> &normal
){
    return incident - (2.0 * dot(normal, incident)) * normal;
}

template <class T, int N, int I, int J>
vec<T, N> refract(
    const swizzler<T, N, I> &incident,
    const swizzler<T, N, J> &normal,
    const T &eta
){
    T t = dot(normal, incident);
    T k = T(1) - eta * eta * (T(1) - t * t);
    return k < T(0) ? T(0) :
        eta * incident - (eta * t + sqrt(k)) * normal;
}

template <class T, int N, int I, int J, int K>
vec<T, N> faceforward(
    const swizzler<T, N, I> &normal,
    const swizzler<T, N, I> &incident,
    const T &normal_ref
){
    return dot(normal_ref, incident) < T(0) ? normal : -normal;
}

}
