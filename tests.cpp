#include "cppglsl/cppglsl.hpp"

using namespace cppglsl;

#include <stdio.h>
#include <assert.h>

int main(){

    // GLSL standard requires that the matrix initialization paremters are transposed.
    // I find this very confusing, but that's the way it is.
    mat2 m = mat2(2.0, 3.0, 5.0, 7.0);

    vec2 a = vec2(11.0, 13.0);

    vec2 b = m * a;

    assert(b.x == 87.0);
    assert(b.y == 124.0);

    vec2 c = a * m;

    assert(c.x == 61.0);
    assert(c.y == 146.0);

    vec2 d = m * a.xy;

    assert(d.x == 87.0);
    assert(d.y == 124.0);

    vec2 e = a.xy * m;

    assert(e.x == 61.0);
    assert(e.y == 146.0);

    assert(m*m == mat2(19.0, 27.0, 45.0, 64.0));

    mat<double, 2, 3> p;
    mat<double, 3, 2> q;
    mat<double, 2, 2> r;

    p[0][0] = 2.0; p[1][0] = 5.0; p[2][0] = 11.0;
    p[0][1] = 3.0; p[1][1] = 7.0; p[2][1] = 13.0;

    q[0][0] = 17.0; q[1][0] = 29.0;
    q[0][1] = 19.0; q[1][1] = 31.0;
    q[0][2] = 23.0; q[1][2] = 37.0;

    r[0][0] = 382.0; r[1][0] = 620.0;
    r[0][1] = 483.0; r[1][1] = 785.0;

    assert(p*q == r);

    mat3 u = mat3(3.0, 11.0, 19.0, 5.0, 13.0, 23.0, 7.0, 17.0, 29.0);
    mat3 v = mat3(31.0, 43.0, 59.0, 37.0, 47.0, 61.0, 41.0, 53.0, 67.0);
    mat3 w = mat3(721.0, 1903.0, 3289.0, 773.0, 2055.0, 3553.0, 857.0, 2279.0, 3941.0);

    assert(u*v == w);

    mat4 f = mat4(2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53);
    mat4 g = mat4(59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131);
    mat4 h = mat4(1585, 1655, 1787, 1861, 5318, 5562, 5980, 6246, 10514, 11006, 11840, 12378, 15894, 16634, 17888, 18710);

    f = transpose(f);
    g = transpose(g);
    h = transpose(h);

    assert(f*g == h);

    printf("tests passed\n");

    return 0;
}
