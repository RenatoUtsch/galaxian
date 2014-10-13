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

#ifndef SYSTEM_INPUT_H
#define SYSTEM_INPUT_H

/**
 * Input System.
 **/

/* Our incomplete types. */
struct GLFWwindow;

/**
 * Inits the input system.
 **/
void inputInit();

/**
 * Terminates the input system.
 **/
void inputTerminate();

/**
 * Updates the input simulation of the game.
 **/
void inputUpdate();

/**
 * GLFW event that asks to close the game (window).
 * You can generate this event by calling this function.
 * See GLFW's glfwSetWindowCloseCallback() for information about this function.
 **/
void closeEvent(struct GLFWwindow *window);

/**
 * GLFW event that represents key input.
 * You can generate this event by calling this function with the appropriate
 * arguments.
 * See GLFW's glfwSetKeyCallback() for information about this function.
 **/
void keyEvent(struct GLFWwindow *window, int key, int scancode, int action, int mods);

/**
 * GLFW event that represents cursor movement.
 * You can generate this event by calling this function with the appropriate
 * arguments.
 * See GLFW's glfwSetCursorPosCallback() for information about this function.
 **/
void cursorPosEvent(struct GLFWwindow *window, double xpos, double ypos);

/**
 * GLFW event that represents mouse input.
 * You can generate this event by calling this function with the appropriate
 * arguments.
 * See GLFW's glfwSetMouseButtonCallback() for information about this function.
 **/
void mouseButtonEvent(struct GLFWwindow *window, int button, int action, int mods);

#endif /* !SYSTEM_INPUT_H */
