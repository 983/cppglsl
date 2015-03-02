#pragma once

#include "vec.hpp"

#include <stdint.h>
#include <stdlib.h>
#include <math.h>

namespace cppglsl {

template <class T, int N_INDEX, int N_COLORS>
struct sampler {

    uint8_t *buf;
    int dim[N_INDEX];

    sampler(): buf(nullptr){
        for (int i = 0; i < N_INDEX; i++) dim[i] = 0;
    }

    sampler(int dim[N_INDEX]){
        for (int i = 0; i < N_INDEX; i++) this->dim[i] = dim[i];
        buf = (uint8_t*)malloc(size());
    }

          uint8_t* data()       { return buf; }
    const uint8_t* data() const { return buf; }

    int size() const {
        int product = 1;
        for (int i = 0; i < N_INDEX; i++) product *= dim[i];
        return product*N_COLORS;
    }

    sampler& operator = (const sampler &a){
        for (int i = 0; i < N_INDEX; i++) this->dim[i] = a.dim[i];
        free(buf);
        buf = (uint8_t*)malloc(size());
        for (int i = 0; i < size(); i++) buf[i] = a.buf[i];
        return *this;
    }

    sampler(const sampler &a): buf(nullptr){
        *this = a;
    }

    ~sampler(){
        free(buf);
    }

    static int repeat(int i, int n){
        int j = i % n;
        return j < 0 ? j + n : j;
    }
/*
    template <class S>
    vec<T, N_COLORS> operator [] (const vec<S, N_INDEX> &a) const {

        int index = 0;
        int p = 1;
        for (int i = 0; i < N_INDEX; i++){
            int d = dim[i];
            int j = a[i]*d;

            j = repeat(j, d);

            index += j*p;
            p *= d;
        }
        index *= N_COLORS;

        vec<T, N_COLORS> v;

        for (int i = 0; i < N_COLORS; i++) v[i] = data()[index + i];

        return v * T(1.0 / 255.0);
    }
    */

    vec<T, N_COLORS> operator () (int x, int y) const {

        x = repeat(x, dim[0]);
        y = repeat(y, dim[1]);

        int index = x + y*dim[1];

        index *= N_COLORS;

        vec<T, N_COLORS> v;

        for (int i = 0; i < N_COLORS; i++) v[i] = data()[index + i];

        return v * T(1.0 / 255.0);
    }

    vec<T, N_COLORS> lerp(const vec<T, N_COLORS> &a, const vec<T, N_COLORS> &b, T u) const {
        vec<T, N_COLORS> c;
        for (int i = 0; i < 4; i++) c[i] = a[i] + u*(b[i] - a[i]);
        return c;
    }

    template <class S>
    vec<T, N_COLORS> operator [] (const vec<S, N_INDEX> &a) const {

        double x = a.x * dim[0];
        double y = a.y * dim[1];

        int ix = floor(x);
        int iy = floor(y);
        double fx = x - ix;
        double fy = y - iy;

        // nearest filtering
        //return (*this)(ix, iy);

        // linear filtering
        vec<T, 4> c00 = (*this)(ix + 0, iy + 0);
        vec<T, 4> c01 = (*this)(ix + 0, iy + 1);
        vec<T, 4> c10 = (*this)(ix + 1, iy + 0);
        vec<T, 4> c11 = (*this)(ix + 1, iy + 1);

        vec<T, 4> c0 = lerp(c00, c01, fy);
        vec<T, 4> c1 = lerp(c10, c11, fy);
        return         lerp(c0 , c1 , fx);
    }
};

template <class T, int N_COLORS, class S>
vec<T, N_COLORS> texture2D(const sampler<T, 2, N_COLORS> &a, const vec<S, 2>  &b, double bias = 0.0){
    return a[b];
}

}
