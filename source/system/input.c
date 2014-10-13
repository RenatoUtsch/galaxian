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

#include <GLFW/glfw3.h>
#include "input.h"
#include "../engine.h"
#include "../objects.h"

void inputInit() {
    // Disappear with the fucking cursor.
    glfwSetInputMode(gWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void inputTerminate() {
    // Nothing to do here.
}

void inputUpdate() {
    double xpos, ypos;
    // Get cursor position.
    glfwGetCursorPos(gWindow, &xpos, &ypos);

    // Calculate the hero's velocity given his position difference with xpos.
    // Only if he is alive. If he isn't, set it as 0.
    if(gHero.exists) {
        gHero.physics.vel.x = HERO_VEL_EQ(gHero.physics.pos.x +
                gHero.renderer.texture.width / 2, xpos);
    }
    else {
        gHero.physics.vel.x = 0;
    }
}

void closeEvent(GLFWwindow *window) {
    setState(CloseState);
}

/// Callback for handling key input from glfw.
void keyEvent(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE)
        setState(CloseState);
    else if(key == GLFW_KEY_R)
        setState(RestartState);
}

/// Callback for handling cursor movement from glfw.
void cursorPosEvent(GLFWwindow *window, double xpos, double ypos) {
    // Set the hero's xpos.
    gHero.input.xpos = xpos;

    // Fix the cursor's x position if it is before or after the screen's width.
    if(xpos < 0)
        glfwSetCursorPos(window, 0, ypos);
    if(xpos > gWidth)
        glfwSetCursorPos(window, gWidth, ypos);
}

/// Callback for handling mouse button input from glfw.
void mouseButtonEvent(GLFWwindow *window, int button, int action, int mods) {
    // Only check for pressed buttons, not released.
    // Also, no modifiers must have been pressed.
    if(action == GLFW_PRESS && !mods) {
        if(button == GLFW_MOUSE_BUTTON_LEFT) {
            // If the button is the left mouse button, fire a shot if one hasn't
            // already been fired and the hero is alive.
            if(!gHeroProjectile.exists && gHero.exists) {
                // Set the position as right after the hero.
                gHeroProjectile.physics.pos.x = gHero.physics.pos.x +
                    gHero.renderer.texture.width / 2;
                gHeroProjectile.physics.pos.y = gHero.physics.pos.y +
                    gHero.renderer.texture.height;

                // Set the velocity.
                gHeroProjectile.physics.vel.y = PROJECTILE_VELOCITY;

                // Set the projectile as existent.
                gHeroProjectile.exists = true;
            }
        }
        else if(button == GLFW_MOUSE_BUTTON_RIGHT) {
            // If the button is the right mouse button, pause if isn't paused or
            // unpause if is paused.
            State state = getState();
            if(state == PauseState)
                setState(RunState);
            else
                setState(PauseState);
        }
        else if(button == GLFW_MOUSE_BUTTON_MIDDLE) {
            // If the button is the middle mouse button, go to step mode and print
            // a value if the game was in step mode or pause mode, or go to pause
            // mode.
            State state = getState();
            if(state == PauseState) {
                stepNextFrame(true);
            }
            else {
                setState(PauseState);
            }

            // But anyways, print the game objects to stdout.
            printObjects();
        }
    }
}

