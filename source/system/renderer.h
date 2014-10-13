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

#ifndef SYSTEM_RENDERER_H
#define SYSTEM_RENDERER_H

/**
 * Size proportionality for when the screen is resized. Must be applied to
 * the size of all rendered objects.
 **/
#define OBJECT_WIDTH_EQ(size) (size + size * ((gWidth * gHeight) / 1000000.0))

/**
 * Size proportionality for the height for whe nthe screen is resized. Must be
 * applied to the size of all rendered objects.
 **/
#define OBJECT_HEIGHT_EQ(size) (size + size * ((gWidth * gHeight) / 1000000.0))

/** Margin before each hero life. **/
#define HERO_LIFE_X_MARGIN 10

/** Offset of the first hero life + margin. **/
#define HERO_LIFE_X_OFFSET 20

/** Offset of the hero lifes. **/
#define HERO_LIFE_Y_OFFSET 10

/** Hero life width eq. **/
#define HERO_LIFE_WIDTH_EQ OBJECT_WIDTH_EQ(13)

/** Hero life height eq. **/
#define HERO_LIFE_HEIGHT_EQ OBJECT_HEIGHT_EQ(17)


/**
 * Renderer system.
 **/

/* Our incomplete types. */
struct GLFWwindow;

/**
 * Inits the rendering system.
 **/
void rendererInit();

/**
 * Terminates the rendering system.
 **/
void rendererTerminate();

/**
 * Updates the rendering state, aka renders the game to the screen.
 **/
void updateRenderer();

/**
 * GLFW event that represents window resize.
 * You can generate this event by calling this function with the appropriate
 * arguments.
 * See GLFW's glfwSetWindowSizeCallback() for information about this function.
 **/
void windowSizeEvent(struct GLFWwindow *window, int width, int height);

#endif /* !SYSTEM_RENDER_H */
