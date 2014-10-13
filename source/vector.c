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

#include <math.h>
#include "vector.h"

#ifndef M_PI
#   define M_PI 3.14159265358979323846
#endif

Vector vectorAdd(Vector v1, Vector v2) {
    // As v1 is a copy, change v1 and return it.
    v1.x += v2.x;
    v1.y += v2.y;
    return v1;
}

Vector vectorSub(Vector v1, Vector v2) {
    // As v1 is a copy, change v1 and return it.
    v1.x -= v2.x;
    v1.y -= v2.y;
    return v1;
}

Vector vectorScale(Vector v, float scale) {
    // As v is a copy, change v and return it.
    v.x *= scale;
    v.y *= scale;
    return v;
}

Vector vectorDivScale(Vector v, float scale) {
    // As v is a copy, change v and return it.
    v.x /= scale;
    v.y /= scale;
    return v;
}

float vectorModule(Vector v) {
    return sqrt((v.x * v.x) + (v.y * v.y));
}

Vector vectorNormalize(Vector v) {
    // As v is a copy, change v and return it.
    return vectorDivScale(v, vectorModule(v));
}

float vectorDirection(Vector v) {
    // Is this right?
    return acos(v.x / sqrt(v.x * v.x));
}
