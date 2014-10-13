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

#ifndef COMPONENT_ANIMATION_H
#define COMPONENT_ANIMATION_H

#include <GLFW/glfw3.h>
#include "renderer.h"

/**
 * Represents animation data.
 **/
typedef struct AnimationComponent {
    /** Textures to alter between in the game. **/
    TextureData *textures;

    /** Number of textures to alter. **/
    size_t numTextures;

    /** Current texture. **/
    size_t currentTexture;

    /** If is to show death animation. **/
    bool showDeath;

    /** Rate to change the textures, in frames. **/
    size_t textureChangeRate;
} AnimationComponent;

#endif /* !COMPONENT_ANIMATION_H */
