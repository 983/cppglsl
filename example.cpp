#include "cppglsl/cppglsl.hpp"

#include <GL/glut.h>

int window_width  = 600;
int window_height = 480;

using namespace cppglsl;

// variables like in
// http://www.shadertoy.com
// and
// http://www.glslsandbox.com
double iGlobalTime;
int dim[2] = {256, 256};
sampler2D iChannel0(dim);
vec4 iResolution;
vec4 iMouse = vec4(window_width*0.5, window_height*0.5, 0.0, 0.0);
vec2 mouse = iMouse.xy;
vec2 resolution;
vec4 gl_FragCoord;
vec4 gl_FragColor;
vec4 iChannelResolution[] = {
    vec4((double)dim[0], (double)dim[1], 1.0, 1.0)
};

// I'm sorry
#define float double
#define in
#define time iGlobalTime
#define main glsl_main
#define INOUT(x) x &

//#include "shaders/texture_example.hpp"
//#include "shaders/spiral.hpp"
#include "shaders/fractal.hpp"

#undef float
#undef in
#undef time
#undef main

void on_frame(){
    glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    window_width  = glutGet(GLUT_WINDOW_WIDTH);
    window_height = glutGet(GLUT_WINDOW_HEIGHT);
    iGlobalTime = glutGet(GLUT_ELAPSED_TIME)*0.001;

    iResolution = vec4((double)window_width, (double)window_height, 0.0, 0.0);
    resolution = iResolution.xy;

    uint8_t *pixels = (uint8_t*)malloc(window_width*window_height*4);
    uint8_t *ptr = pixels;

    for (double y = 0.0; y < resolution.y; y++){
        for (double x = 0.0; x < resolution.x; x++){
            gl_FragCoord.xy = vec2(x, y);

            glsl_main();

            gl_FragColor = clamp(gl_FragColor, 0.0, 1.0) * 255.0;
            for (int i = 0; i < 4; i++) *ptr++ = gl_FragColor[i];
        }
    }

    glDrawPixels(window_width, window_height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    free(pixels);

    glutSwapBuffers();
}

void work(int frame){
    glutPostRedisplay();
    glutTimerFunc(20, work, frame + 1);
}

void on_move(int x, int y){
    iMouse.x = x;
    iMouse.y = window_height - 1 - y;
    mouse = iMouse.xy;
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("");
    glutDisplayFunc(on_frame);
    glutMotionFunc(on_move);
    glutPassiveMotionFunc(on_move);

    uint8_t *ptr = iChannel0.data();
    for (int i = 0; i < iChannel0.size(); i += 4){
        *ptr++ = rand() & 255;
        *ptr++ = rand() & 255;
        *ptr++ = rand() & 255;
        *ptr++ = rand() & 255;
    }

    work(0);
    glutMainLoop();

    return 0;
}
