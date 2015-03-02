#include <stdio.h>

FILE *fp = stdout;

void foo(int n, int m){
    const char *xyzw = "xyzw";
    const char *rgba = "rgba";
    const char *stpq = "stpq";

    int i, idx[4];
    for (i = 0; i < 4; i++) idx[i] = 0;

    static int offset = 256;
    offset++;

    while (1){

        fprintf(fp, "    swizzler<T, %i, V1_ENCODE4_5(%i, %i, %i, %i, %i)> ", n, idx[0], idx[1], idx[2], idx[3], offset);

        for (i = 0; i < n; i++) fprintf(fp, "%c", xyzw[idx[i]]);
        fprintf(fp, ", ");
        for (i = 0; i < n; i++) fprintf(fp, "%c", rgba[idx[i]]);
        fprintf(fp, ", ");
        for (i = 0; i < n; i++) fprintf(fp, "%c", stpq[idx[i]]);

        fprintf(fp, ";\\\n");

        for (i = 0; i < 4; i++){
            idx[i]++;
            if (idx[i] < m) break;
            idx[i] = 0;
        }
        if (i == n) break;
    }

}

int main(){

    fp = fopen("swizzling.hpp", "wb");

    fprintf(fp, "#pragma once\n");

    fprintf(fp, "\n\n#define V1_VEC2_SWIZZLE \\\n");
    foo(2, 2);
    foo(3, 2);
    foo(4, 2);
    fprintf(fp, "\n\n#define V1_VEC3_SWIZZLE \\\n");
    foo(2, 3);
    foo(3, 3);
    foo(4, 3);
    fprintf(fp, "\n\n#define V1_VEC4_SWIZZLE \\\n");
    foo(2, 4);
    foo(3, 4);
    foo(4, 4);
    fprintf(fp, "\n\n");

    fclose(fp);

    return 0;
}
