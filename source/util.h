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

#ifndef UTIL_H
#define UTIL_H

#include <GLFW/glfw3.h>

/**
 * Utility functions.
 **/

/**
 * Used when iterating in a normal array by two variables.
 **/
#define AT(i, max_j, j) (((i) * (max_j)) + (j))

/**
 * Sleeps for a higher interval.
 * @param s The number of seconds to sleep.
 **/
void sSleep(unsigned long s);

/**
 * Sleeps.
 * @param ms The number of milliseconds to sleep.
 **/
void pSleep(unsigned long ms);

/**
 * Loads a texture from a file and returns its id.
 * @param filename The filename of the texture.
 **/
GLuint loadTexture(const char *filename);

/**
 * Unloads a texture previously loaded with loadTexture.
 * @param id The id of the texture, returned by loadTexture
 * @param id The id of the texture, returned by loadTexture
 * @see loadTexture()
 **/
void freeTexture(unsigned id);

/**
 * Inits the text write system.
 **/
void initTextSystem(int argc, char **argv);

/**
 * Terminates the text write system.
 **/
void terminateTextSystem();

/**
 * Writes text.
 * initTextSystem() must have been called.
 * @see initTextSystem()
 **/
void writeText(int x, int y, float scale, const char *text);

#endif /* !UTIL_H */
