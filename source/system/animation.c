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

#include "animation.h"
#include "../objects.h"

void animationInit() {

}

void animationTerminate() {

}

void animationUpdate() {
    static int rate = -1; // Will get to 0 on the first iteration.
    static int heroDeathRate = 0;
    size_t i;

    // Set the renderer values depending on the rate.
    rate = (rate + 1) % ANIMATION_RATE;
    for(i = 0; i < gEnemiesEnd; ++i) {
        if(!gEnemies[i].animation.showDeath) {
            // Set the alive enemies texture.
            if(!rate) {
                if(gEnemies[i].exists) {
                    // Set the next texture.
                    gEnemies[i].animation.currentTexture =
                        (gEnemies[i].animation.currentTexture + 1) % ENEMY_ALIVE_TEXTURES;
                    gEnemies[i].renderer.texture =
                        gEnemies[i].animation.textures[gEnemies[i].animation.currentTexture];
                }
            }
        }
        else {
            // Show the death texture.

            if(!rate) {
                // Get the next texture.
                if(++gEnemies[i].animation.currentTexture == ENEMY_NUM_TEXTURES) {
                    // Reset the texture to the normal texture of the enemy.
                    gEnemies[i].animation.currentTexture = 0;
                    gEnemies[i].animation.showDeath = false;
                }

                // Set the next texture.
                gEnemies[i].renderer.texture =
                    gEnemies[i].animation.textures[gEnemies[i].animation.currentTexture];
            }
        }
    }

    // Show the hero's death.
    if(gHero.animation.showDeath) {
        heroDeathRate = (rate + 1) % ANIMATION_RATE;
        if(!heroDeathRate) {
            // Get the next texture.
            if(++gHero.animation.currentTexture == gHero.animation.numTextures) {
                // Reset the texture to the hero's normal texture.
                gHero.animation.currentTexture = 0;
                gHero.animation.showDeath = false;
            }

            // Set the next texture.
            gHero.renderer.texture = gHero.animation.textures[gHero.animation.currentTexture];
        }
    }
}
