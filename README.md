**This project is dead. A glsl to cpp compiler looks like a more promissing approach.**

cppglsl
=======

C++11 implementation of vec2, vec3, vec4, mat2, mat3, mat4, sampler2D with swizzeling.

Example output of fragment shader executed on the CPU:

![Example](https://raw.githubusercontent.com/983/cppglsl/master/output.jpg)

Why:

Many examples on https://www.shadertoy.com/ and http://glslsandbox.com/ only display black on older gpus. With this library most examples can simply be copied and pasted into c++ files and work correctly without modifications.

Another nice thing is debugging since now you can simply add a printf call into your shader.

Example:

    void main(){
        vec2 uv = gl_FragCoord.xy / iResolution.xy;
        uv -= iMouse.xy / iResolution.xy;
        printf("%f %f\n", uv.x, uv.y);
        gl_FragColor = texture2D(iChannel0, uv);
    }

Limitations:
- `out` and `inout` can not be converted to references with macros. Use the fix_inout.py script for that.
- Swizzled members can not be used as `out` or `inout` parameters.
- `dFdx`, `dFdy` and `fwidth` are not supported.
