const float PI = 3.14159;

void main(){
    vec2 uv = gl_FragCoord.xy / iResolution.xy * 2.0 - 1.0;
    uv.x *= iResolution.x/iResolution.y;

    float r = length(uv);
    float a = atan(uv.y, uv.x)*10.0;
    a += iGlobalTime*10.0;
    a += log(r)*50.0;

    float g = cos(mod(a, PI)*2.0)*0.5 + 0.5;

    g *= smoothstep(0.0, 0.7, r);

    gl_FragColor = vec4(g);
}
