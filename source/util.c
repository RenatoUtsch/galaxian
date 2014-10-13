/*
 * Autor: Renato Utsch Gonçalves
 * Ciência da Computação, UFMG
 * Computação Gráfica
 * Trabalho Prático 1 - Galaxian
 *
 * Copyright (c) 2014 Renato Utsch
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "util.h"
#include "engine.h"

#ifdef _WIN32
#   include <windows.h>
#else
#   include <unistd.h>
#endif

#include <errno.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#ifdef __APPLE__
#   include <GLUT/glut.h>
#else
#   include <GL/glut.h>
#endif

void sSleep(unsigned long s) {
#ifdef _WIN32
    Sleep(s * 1000);
#else
    sleep(s);
#endif
}

void pSleep(unsigned long ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    struct timespec tim, tim2;

    tim.tv_sec = 0;
    tim.tv_nsec = ms * 1000;
    if(nanosleep(&tim, &tim2))
        error(0, "Failed to sleep.");
#endif
}

GLuint loadTexture(const char *filename) {
    GLuint texture = SOIL_load_OGL_texture(filename,
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            0);
    if(!texture) {
        fprintf(stderr, "file: %s\n", filename);
        error(0, SOIL_last_result());
    }

    return texture;
}

void freeTexture(GLuint id) {
    glDeleteTextures(1, &id);
}

void initTextSystem(int argc, char **argv) {
    glutInit(&argc, argv);
}

void terminateTextSystem() {

}

void writeText(int x, int y, float scale, const char *text) {
    // Okay, ugly hack to use glut to write text, but I don't have
    // enough time to go looking for an alternative.
    int len, i;
    len = (int) strlen(text);

    glPushMatrix();
    glLoadIdentity();

    glTranslatef(x, y, 0);
    glScalef(scale, scale, scale);

    for(i = 0; i < len; ++i) {
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, text[i]);
    }

    glPopMatrix();


}
