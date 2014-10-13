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

#ifndef VECTOR_H
#define VECTOR_H

/**
 * Vector type and operations.
 **/

/**
 * Represents a vector.
 **/
typedef struct Vector {
    /** Values in x and y directions. **/
    float x, y;
} Vector;

/**
 * Adds vectors v1 and v2 and returns the result.
 **/
Vector vectorAdd(Vector v1, Vector v2);

/**
 * Subtracts vector v2 from v1 and returns the result.
 **/
Vector vectorSub(Vector v1, Vector v2);

/**
 * Scales the vector v by multiplying by the given scale and returns the
 * result.
 **/
Vector vectorScale(Vector v, float scale);

/**
 * Scales the vector v by dividing by the given scale and returns the result.
 **/
Vector vectorDivScale(Vector v, float scale);

/**
 * Returns the vector's module.
 **/
float vectorModule(Vector v);

/**
 * Returns the normalized version of v.
 **/
Vector vectorNormalize(Vector v);

/**
 * Returns the vector's direction in radians.
 **/
float vectorDirection(Vector v);

#endif /* !VECTOR_H */
