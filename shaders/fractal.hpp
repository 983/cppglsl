#define ITERATIONS 20

float fractal(vec3 p, vec3 c) {
    float s = 4.0;
    float sum0 = 0.0;
    float sum1 = 0.0;
    float prev = 0.0;

    for (int i = 0; i < ITERATIONS; i++){
        float f = dot(p, p);

        p = abs(p) / f - c;

        float weight = exp(-float(i) / s);

        sum0 += weight * exp(-s * abs(f - prev));
        sum1 += weight;

        prev = f;
    }
    
    return s * sum0 / sum1;
}

vec3 gradient(float f){

    float step0 = 0.0;
    float step1 = 0.6;
    float step2 = 0.8;
    float step3 = 0.9;
    float step4 = 1.0;

    vec3 c =   vec3(0.0, 0.0, 0.0);
    c = mix(c, vec3(0.4, 0.1, 0.1), smoothstep(step0, step1, f));
    c = mix(c, vec3(1.0, 0.0, 0.0), smoothstep(step1, step2, f));
    c = mix(c, vec3(0.9, 0.8, 0.2), smoothstep(step2, step3, f));
    c = mix(c, vec3(0.9, 0.9, 1.0), smoothstep(step3, step4, f));

    return c;
}

void main() {
    vec2 offset = iMouse.xy / iResolution.xy * 2.0 - 1.0;
    vec2 uv = gl_FragCoord.xy  / iResolution.xy * 2.0 - 1.0;
    uv -= offset;

    vec4 c = sin(vec4(1.0, 2.0, 3.0, 5.0)*iGlobalTime * 0.2) * 0.5 + 0.5;

    c.xy = c.xy*0.2 + 0.5;
    c.z = c.z*1.5;
    c.w = c.w*0.1 - 0.05;

    float f = fractal(vec3(uv, c.w), vec3(c.xyz));

    gl_FragColor = vec4(gradient(f), 1.0);
}
