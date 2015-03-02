#pragma once

namespace cppglsl {

// quaternary encoding/decoding
// if you understand hexadecimal, you understand this
#define V1_ENCODE4_5(i0, i1, i2, i3, i4) ((i0) + ((i1) << 2) + ((i2) << 4) + ((i3) << 6) + ((i4) << 8))
#define V1_DECODE4(I, i) ((I >> (i + i)) & 3)

// a.xy = a.yx and similar requires temporary storage
#define V1_SAFE_COPY(src, dst, tmp, N) \
    T tmp[N]; \
    for (int i = 0; i < N; i++) (tmp)[i] = (src)[i];\
    for (int i = 0; i < N; i++) (dst)[i] = (tmp)[i];

template <class T, int N, int I>
struct swizzler {

    swizzler(){}

                     swizzler             (const swizzler          &a){ V1_SAFE_COPY(a, *this, tmp, N) }
                     swizzler& operator = (const swizzler          &a){ V1_SAFE_COPY(a, *this, tmp, N) return *this; }
    template <int J> swizzler             (const swizzler<T, N, J> &a){ V1_SAFE_COPY(a, *this, tmp, N) }
    template <int J> swizzler& operator = (const swizzler<T, N, J> &a){ V1_SAFE_COPY(a, *this, tmp, N) return *this; }

          T& operator [] (int i)       { return ((T*)this)[V1_DECODE4(I, i)]; }
    const T& operator [] (int i) const { return ((T*)this)[V1_DECODE4(I, i)]; }

#define V1_SWIZZLER_SWIZZLER_OP(op) \
    template <int J>\
    void operator op (const swizzler<T, N, J> &a){\
        T temp[N];\
        for (int i = 0; i < N; i++) temp[i] = a[i];\
        for (int i = 0; i < N; i++) (*this)[i] op temp[i];\
    }

#define V1_SWIZZLER_SCALAR_OP(op) \
    void operator op (T a){\
        for (int i = 0; i < N; i++) (*this)[i] op a;\
    }

    V1_SWIZZLER_SWIZZLER_OP(+=)
    V1_SWIZZLER_SWIZZLER_OP(-=)
    V1_SWIZZLER_SWIZZLER_OP(*=)
    V1_SWIZZLER_SWIZZLER_OP(/=)

    V1_SWIZZLER_SCALAR_OP(+=)
    V1_SWIZZLER_SCALAR_OP(-=)
    V1_SWIZZLER_SCALAR_OP(*=)
    V1_SWIZZLER_SCALAR_OP(/=)


};

}
