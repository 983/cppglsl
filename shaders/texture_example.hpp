void main(){
    vec2 uv = gl_FragCoord.xy / iResolution.xy;
    uv -= iMouse.xy / iResolution.xy;
    gl_FragColor = texture2D(iChannel0, uv);
}
