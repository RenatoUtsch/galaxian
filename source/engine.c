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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <GLFW/glfw3.h>
#include "engine.h"
#include "objects.h"
#include "system/ai.h"
#include "system/animation.h"
#include "system/input.h"
#include "system/physics.h"
#include "system/renderer.h"
#include "util.h"

/// Current game state.
State gState;

/// If is to step the next frame (only matters if state is StepState).
bool gStep;

/// GLFW window.
GLFWwindow *gWindow;

/// Window width.
int gWidth;

/// Window height.
int gHeight;

/// Count of fps.
unsigned long gFpsCount;

/// Highscore.
int gHighscore;

/**
 * Inits the GLFW window system.
 **/
static void initWindowSystem() {
    // GLFW initialization.
    if(!glfwInit())
        exit(2);

    // Window size.
    gWidth = 640;
    gHeight = 480;

    // Window initialization.
    gWindow = glfwCreateWindow(gWidth, gHeight, "Galaxian", NULL, NULL);
    if(!gWindow) {
        glfwTerminate();
        exit(2);
    }
    glfwSetWindowPos(gWindow, 100, 100);
    glfwMakeContextCurrent(gWindow);

    // Callbacks.
    glfwSetErrorCallback(error);
    glfwSetWindowSizeCallback(gWindow, windowSizeEvent);
    glfwSetWindowCloseCallback(gWindow, closeEvent);
    glfwSetKeyCallback(gWindow, keyEvent);
    glfwSetCursorPosCallback(gWindow, cursorPosEvent);
    glfwSetMouseButtonCallback(gWindow, mouseButtonEvent);
}

/**
 * Terminates the GLFW window system.
 **/
static void terminateWindowSystem() {
    glfwDestroyWindow(gWindow);
    glfwTerminate();
}

/**
 * Processes the game state and receives events from GLFW.
 **/
static bool processState()
{
    if(gState == RunState)
        glfwPollEvents(); // Receive inputs
    else if(gState == PauseState) {
        // While we are in this state and we are not asked to step, continue
        // ignoring input.
        gStep = false;
        while(gState == PauseState && !gStep)
            glfwWaitEvents();
    }
    else
        return false;

    return true;
}

void error(int error, const char *description) {
    // Print the error, terminate and exit.
    fprintf(stderr, "%s (Error %d)", description, error);
    exit(3);
}

void stepNextFrame(bool step) {
    gStep = step;
}


void setState(State state) {
    gState = state;
}

State getState() {
    return gState;
}

void endGame() {
    char win[] = "You win!";
    char lose[] = "You lose.";

    // Increase the score by the number of lifes left. Only if he is
    // alive.
    if(gHero.exists)
        gHero.score += LIFE_SCORE * (gHero.lifes + 1);
    updateRenderer();

    // Show a you win or a you lost message and exit.
    glColor4f(1.0, 0.0, 0.0, 1.0);
    writeText(gHeight / 4, gWidth / 4, 0.5, gEnemiesEnd == 0 ? win : lose);
    glfwSwapBuffers(gWindow);

    // Sleep for 3 seconds.
    sSleep(3);

    // Exit.
    setState(CloseState);
}

/// Loads highscore from file if it exists.
static void loadHighscore() {
    int ret;
    FILE *fp = fopen(HIGHSCORE_FILE, "r");
    gHighscore = 0;

    if(!fp)
        return;

    ret = fscanf(fp, "%d", &gHighscore);
    if(ret != 1)
        gHighscore = 0;

    fclose(fp);
}

/// Saves highscore to the file.
static void saveHighscore() {
    FILE *fp = fopen(HIGHSCORE_FILE, "wt");
    if(!fp)
        return;

    fprintf(fp, "%d", gHighscore);
    fclose(fp);
}

void init(int argc, char **argv) {
    // Initialize the rand() function.
    srand(time(NULL));

    // Init the windowing system.
    initWindowSystem();

    // Init the text drawing system.
    initTextSystem(argc, argv);

    // Load the highscore.
    loadHighscore();

    // Init our systems.
    aiInit();
    animationInit();
    inputInit();
    physicsInit();
    rendererInit();
}

void load() {
    // Init the game data.
    objectsInit();
}

void unload() {
    // Terminate the game data.
    objectsTerminate();
}

void terminate() {
    // Terminate our systems.
    aiTerminate();
    animationTerminate();
    inputTerminate();
    physicsTerminate();
    rendererTerminate();

    // Save the highscore.
    saveHighscore();

    // Terminate the text system.
    terminateTextSystem();

    // Clean up the windowing system.
    terminateWindowSystem();
}

void mainLoop() {
    const double fpsTime = 1000 / FPS;
    double sleepTime;
    double t1, t2;
    gFpsCount = 0;

    // Main loop.
    for(;;) {
        ++gFpsCount;
        if(!processState())
            break;

        t1 = glfwGetTime();

        // Update the game simulation and then render.
        aiUpdate();
        animationUpdate();
        inputUpdate();
        physicsUpdate(fpsTime);
        updateRenderer();

        t2 = glfwGetTime();

        // Get the sleep time.
        sleepTime = fpsTime - (t2 - t1);

        // Sleep for the rest of the frame.
        if(sleepTime > 0.0)
            pSleep(sleepTime);
        else
            fprintf(stderr, "Can't keep up!\n");
    }
}

