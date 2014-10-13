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

#define GLFW_INCLUDE_GLU
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include "renderer.h"
#include "../engine.h"
#include "../objects.h"
#include "../util.h"

/// Maximum number of stars.
#define MAX_STARS 2000

/// Size of the background stars.
#define STAR_SIZE 2.2

/// Background refresh rate. The value is arbitrary.
#define BG_REFRESH_RATE 6

/// Star descent rate. The vale is arbitrary and is a float.
#define STAR_DESCENT_RATE 1.2

/// Score X offset.
#define SCORE_X_OFFSET 50

/// Score Y offset.
#define SCORE_Y_OFFSET (gHeight - 30)

/// Score's text scale.
#define SCORE_SCALE 0.2

/**
 * Represents a star in the background.
 **/
typedef struct Star {
    /// Position.
    Vector pos;

    /// Color.
    float r, g, b;
} Star;

/// Background stars.
static Star gStars[MAX_STARS];

/// Number of stars.
static int gNumStars;

/// Texture of the hero's lifes.
static GLuint gHeroLifeTexture;

/// Width of the hero's lifes.
static float gHeroLifeWidth;

/// Height of the hero's lifes.
static float gHeroLifeHeight;

/**
 * Renders the background.
 **/
static void renderBackground() {
    static int refresh_rate = -1; // Will get to 0 on next command.
    int i;

    // Update the background if the refresh rate is 0.
    refresh_rate = (refresh_rate + 1) % BG_REFRESH_RATE;
    if(!refresh_rate) {
        // Randomly generate the color of the stars.
        for(i = 0; i < gNumStars; ++i) {
            // Randomize if the star is lit or not.
            if(rand() % 2) {
                gStars[i].r = (rand() % 256) / 256.0;
                gStars[i].g = (rand() % 256) / 256.0;
                gStars[i].b = (rand() % 256) / 256.0;
            }
            else {
                gStars[i].r = 0.0;
                gStars[i].g = 0.0;
                gStars[i].b = 0.0;
            }
        }
    }

    // Update the position.
    for(i = 0; i < gNumStars; ++i) {
        gStars[i].pos.y -= STAR_DESCENT_RATE;
        if(gStars[i].pos.y < 0) { // Reset the position at the beginning.
            gStars[i].pos.x = rand() % gWidth;
            gStars[i].pos.y = gHeight;
        }
    }

    // Render the background.
    for(i = 0; i < gNumStars; ++i) {
        glColor4f(gStars[i].r, gStars[i].g, gStars[i].b, 0.5);
        glBegin(GL_QUADS);
            glVertex2f(gStars[i].pos.x, gStars[i].pos.y);

            glVertex2f(gStars[i].pos.x, gStars[i].pos.y + STAR_SIZE);

            glVertex2f(gStars[i].pos.x + STAR_SIZE, gStars[i].pos.y + STAR_SIZE);

            glVertex2f(gStars[i].pos.x + STAR_SIZE, gStars[i].pos.y);
        glEnd();
        glBegin(GL_POINTS);
            glVertex2f(gStars[i].pos.x, gStars[i].pos.y);
        glEnd();
    }
}

/**
 * Renders the hero's lifes.
 **/
static void renderHeroLifes() {
    int i;
    float x, y;

    glColor4f(1.0, 1.0, 1.0, 0.8);

    // Enable texture rendering.
    glEnable(GL_TEXTURE_2D);

    // Bind the texture.
    glBindTexture(GL_TEXTURE_2D, gHeroLifeTexture);

    // Render the lifes.
    for(i = 0; i < gHero.lifes; ++i) {
        // Calculate x and y of the life.
        x = HERO_LIFE_X_OFFSET + i * (gHeroLifeWidth + HERO_LIFE_X_MARGIN);
        y = HERO_LIFE_Y_OFFSET;

        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0);
            glVertex2f(x, y);

            glTexCoord2f(0.0, 0.0);
            glVertex2f(x, y + gHeroLifeHeight);

            glTexCoord2f(1.0, 0.0);
            glVertex2f(x + gHeroLifeWidth, y + gHeroLifeHeight);

            glTexCoord2f(1.0, 1.0);
            glVertex2f(x + gHeroLifeWidth, y);
        glEnd();
    }

    // Disable texture rendering to draw everything else.
    glDisable(GL_TEXTURE_2D);
}

/**
 * Renders the hero.
 **/
static void renderHero() {
    // If the hero is dead, do not render him.
    if(!gHero.exists && !gHero.animation.showDeath)
        return;

    glColor4f(1.0, 1.0, 1.0, 0.8);

    // Enable texture rendering.
    glEnable(GL_TEXTURE_2D);

    // Bind the texture.
    glBindTexture(GL_TEXTURE_2D, gHero.renderer.texture.id);

    // Render the hero.
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0);
        glVertex2f(gHero.physics.pos.x, gHero.physics.pos.y);

        glTexCoord2f(0.0, 0.0);
        glVertex2f(gHero.physics.pos.x, gHero.physics.pos.y +
                gHero.renderer.texture.height);

        glTexCoord2f(1.0, 0.0);
        glVertex2f(gHero.physics.pos.x + gHero.renderer.texture.width,
                gHero.physics.pos.y + gHero.renderer.texture.height);

        glTexCoord2f(1.0, 1.0);
        glVertex2f(gHero.physics.pos.x + gHero.renderer.texture.width,
                gHero.physics.pos.y);
    glEnd();

    // Disable texture rendering to draw everything else.
    glDisable(GL_TEXTURE_2D);
}

/**
 * Renders the enemies.
 **/
static void renderEnemies() {
    size_t i;

    glColor4f(1.0, 1.0, 1.0, 0.8);

    // Enable texture rendering.
    glEnable(GL_TEXTURE_2D);

    for(i = 0; i < gEnemiesEnd; ++i) {
        // Only render if it is alive or if is to show his death.
        if(gEnemies[i].exists || gEnemies[i].animation.showDeath) {
            // Bind the texture.
            glBindTexture(GL_TEXTURE_2D, gEnemies[i].renderer.texture.id);

            // Render the enemy.
            glBegin(GL_QUADS);
                glTexCoord2f(0.0, 1.0);
                glVertex2f(gEnemies[i].physics.pos.x, gEnemies[i].physics.pos.y);

                glTexCoord2f(0.0, 0.0);
                glVertex2f(gEnemies[i].physics.pos.x, gEnemies[i].physics.pos.y +
                        gEnemies[i].renderer.texture.height);

                glTexCoord2f(1.0, 0.0);
                glVertex2f(gEnemies[i].physics.pos.x + gEnemies[i].renderer.texture.width,
                        gEnemies[i].physics.pos.y + gEnemies[i].renderer.texture.height);

                glTexCoord2f(1.0, 1.0);
                glVertex2f(gEnemies[i].physics.pos.x + gEnemies[i].renderer.texture.width,
                        gEnemies[i].physics.pos.y);
            glEnd();
        }
    }
}

static void renderScore() {
    char score[42];
    char high[42];

    // Update the highscore.
    if(gHero.score > gHighscore)
        gHighscore = gHero.score;

    // Convert the score to string.
    sprintf(score, "Score: %02d", gHero.score);
    sprintf(high, "Highscore: %02d", gHighscore);

    // We want a yellow score.
    glColor4f(1.0, 0.0, 0.0, 1.0);

    // Write the score.
    writeText(SCORE_X_OFFSET, SCORE_Y_OFFSET, SCORE_SCALE, score);
    writeText(SCORE_X_OFFSET * 6, SCORE_Y_OFFSET, SCORE_SCALE, high);
}

/**
 * Renders the UI.
 **/
static void renderUi() {
    // Render the hero lifes.
    renderHeroLifes();

    // Render the score.
    renderScore();
}

/**
 * Renders the projectiles.
 **/
static void renderProjectiles() {
    size_t i;

    // Render hero's projectiles.
    // Only render it if the hero exists.
    if(gHero.exists) {
        glColor4f(1.0, 1.0, 0.0, 1.0);
        glBegin(GL_QUADS);
            glVertex2f(gHeroProjectile.physics.pos.x, gHeroProjectile.physics.pos.y);

            glVertex2f(gHeroProjectile.physics.pos.x,
                    gHeroProjectile.physics.pos.y + PROJECTILE_HEIGHT);

            glVertex2f(gHeroProjectile.physics.pos.x + PROJECTILE_WIDTH,
                    gHeroProjectile.physics.pos.y + PROJECTILE_HEIGHT);

            glVertex2f(gHeroProjectile.physics.pos.x + PROJECTILE_WIDTH,
                    gHeroProjectile.physics.pos.y);
        glEnd();
    }

    // Render the projectiles of the enemies.
    glColor4f(0.5, 0.5, 0.5, 1.0);
    for(i = 0; i < gEnemyProjectilesEnd; ++i) {
        if(gEnemyProjectiles[i].exists) {
            glBegin(GL_QUADS);
                glVertex2f(gEnemyProjectiles[i].physics.pos.x,
                        gEnemyProjectiles[i].physics.pos.y);

                glVertex2f(gEnemyProjectiles[i].physics.pos.x,
                        gEnemyProjectiles[i].physics.pos.y + PROJECTILE_HEIGHT);

                glVertex2f(gEnemyProjectiles[i].physics.pos.x + PROJECTILE_WIDTH,
                        gEnemyProjectiles[i].physics.pos.y + PROJECTILE_HEIGHT);

                glVertex2f(gEnemyProjectiles[i].physics.pos.x + PROJECTILE_WIDTH,
                        gEnemyProjectiles[i].physics.pos.y);
            glEnd();
        }
    }
}

/**
 * Generates the stars based on screen's width and height.
 **/
static void generateStars() {
    int i;

    // Generate the number of stars.
    gNumStars = gWidth * gHeight / 1500; // Arbitrary value.

    // Don't forget we have a maximum number of stars.
    if(gNumStars > MAX_STARS)
        gNumStars = MAX_STARS;

    // Generate the position of the stars.
    for(i = 0; i < gNumStars; ++i) {
        gStars[i].pos.x = rand() % gWidth;
        gStars[i].pos.y = rand() % gHeight;
    }
}

/**
 * Inits the game UI.
 **/
static void initUi() {
    // Load the Hero life's sprite.
    gHeroLifeTexture = loadTexture("resource/texture/13.png");
    gHeroLifeWidth = HERO_LIFE_WIDTH_EQ;
    gHeroLifeHeight = HERO_LIFE_HEIGHT_EQ;
}

/**
 * Terminates the game UI.
 **/
static void terminateUi() {
    // Unload the Hero life's sprite.
    freeTexture(gHeroLifeTexture);
}

/**
 * Sets up the OpenGL projection width gWidth and gHeight.
 **/
static void setUpProjection() {
    int framebufferWidth, framebufferHeight;

    // Get the framebuffer size (it is different than the screen size).
    glfwGetFramebufferSize(gWindow, &framebufferWidth, &framebufferHeight);

    // Set up the viewport.
    glViewport(0, 0, framebufferWidth, framebufferHeight);

    // Set up our projection matrix.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, gWidth, 0.0, gHeight);
    glMatrixMode(GL_MODELVIEW);
}

void rendererInit() {
    // Black background.
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // Set up OpenGL's projection.
    setUpProjection();

    // Enable 2D things and disable 3D things.
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Generate the background stars.
    generateStars();

    // Init the UI objects.
    initUi();
}

void rendererTerminate() {
    terminateUi();
}

void updateRenderer() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Render the background first.
    renderBackground();

    // Render the hero.
    renderHero();

    // Render the enemies.
    renderEnemies();

    // Render the UI.
    renderUi();

    // Render the projectiles.
    renderProjectiles();

    // Swap buffers.
    glfwSwapBuffers(gWindow);
}

void windowSizeEvent(GLFWwindow *window, int width, int height) {
    // Save the new width and height.
    gWidth = width;
    gHeight = height;

    // Set up the hero's data.
    updateHeroData();

    // Set up the hero life's data.
    gHeroLifeWidth = HERO_LIFE_WIDTH_EQ;
    gHeroLifeHeight = HERO_LIFE_HEIGHT_EQ;

    // Set up OpenGL's projection again.
    setUpProjection();

    // Regenerate the position of the stars.
    generateStars();
}
