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

#ifndef ENGINE_H
#define ENGINE_H

/**
 * This file stores the main game manipulation functions.
 **/

#include <stdbool.h>

/** Number of fps the game will run at. **/
#define FPS 60

/** How much the fps count will influence score. **/
#define FPS_SCORE_INFLUENCE 20000

/** How much the hero's lifes will influence score. **/
#define LIFE_SCORE 2000

/** Highscore file. **/
#define HIGHSCORE_FILE "resource/highscore.dat"

/* Our incomplete types. */
struct GLFWwindow;

/** Game window. **/
extern struct GLFWwindow *gWindow;

/** Window width. **/
extern int gWidth;

/** Window height. **/
extern int gHeight;

/** Count of fps in the game. **/
extern unsigned long gFpsCount;

/** Highscore. **/
extern int gHighscore;

/** Called when an error occurs. **/
void error(int error, const char *description);

/**
 * Enum that represents state of execution.
 **/
typedef enum State
{
    RunState,
    PauseState,
    RestartState,
    CloseState
} State;

/**
 * Changes the game state to the specified state on the next iteration of the
 * main loop.
 **/
void setState(State state);

/**
 * Gets the current game state.
 **/
State getState();

/**
 * If is to step - set when the user presses the middle mouse button.
 * Only evaluated if the game state is StepState. If not, this function is
 * ignored.
 **/
void stepNextFrame(bool step);

/**
 * Ends the game showing a "You lose!" or "You win!" message.
 **/
void endGame();

/**
 * Initializes the game. Must be called before mainLoop().
 * @see mainLoop().
 **/
void init(int argc, char **argv);

/**
 * Sets up the level. Must be called before mainLoop().
 **/
void load();

/**
 * Ends the level.
 * Must be called after mainLoop().
 **/
void unload();

/**
 * Terminates the game by cleaning everything up.
 * Must be called after mainLoop().
 **/
void terminate();

/**
 * Main loop of the game. This function only returns when the game has ended.
 **/
void mainLoop();

#endif /* !ENGINE_H */
