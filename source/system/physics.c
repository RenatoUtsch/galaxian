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
#include "physics.h"
#include "../engine.h"
#include "../objects.h"

// Resurrects the hero if he is dead.
static void resurrectHero() {
    static int delay = 0;

    if(!gHero.exists) {
        delay = (delay + 1) % HERO_RESURRECT_DELAY;
        if(!delay) {
            /// If the hero doesn't have any more lifes, end the
            /// game.
            if(!gHero.lifes) {
                endGame();
            }

            --gHero.lifes;
            gHero.exists = true;
        }
    }
}

/// Updates the hero's position.
static void moveHero(float dt) {
    // Move the hero by his velocity.
    // Remember, d = d0 + v * t
    gHero.physics.pos.x += gHero.physics.vel.x * dt;

    // If the hero is after the end of the screen, put him at the end of the
    // screen.
    if(gHero.physics.pos.x > gWidth - gHero.renderer.texture.width)
        gHero.physics.pos.x = gWidth - gHero.renderer.texture.width;
    else if(gHero.physics.pos.x < 0)
        gHero.physics.pos.x = 0;
}

/// Updates the position of the hero's projectile.
static void moveHeroProjectile(float dt) {
    // Move if it exists. Else, make it follow the hero.
    if(gHeroProjectile.exists) {
        // Remember, d = d0 + v * t;
        gHeroProjectile.physics.pos.y += gHeroProjectile.physics.vel.y * dt;

        // If it is outside the space, set it as nonexistent.
        if(gHeroProjectile.physics.pos.y > gHeight)
            gHeroProjectile.exists = false;
    }
    else {
        gHeroProjectile.physics.pos.x = gHero.physics.pos.x +
            gHero.renderer.texture.width / 2 - PROJECTILE_WIDTH / 2;
        gHeroProjectile.physics.pos.y = gHero.physics.pos.y +
            gHero.renderer.texture.height;
    }
}

/// Updates the position of the enemies.
static void moveEnemies(float dt) {
    size_t i;
    Vector vel;

    // Set up the velocities. It is only needed to get the first existing velocity.
    for(i = 0; i < gEnemiesEnd; ++i) {
        if(gEnemies[i].exists) {
            vel.x = gEnemies[i].physics.vel.x;
            break;
        }
    }

    // If any enemy is at the border of the screen, change the direction of
    // the velocity.
    for(i = 0; i < gEnemiesEnd; ++i) {
        if(gEnemies[i].exists) {
            // Change direction if the current is positive.
            // Doesn't need to test if the velocity is equal to 0.
            if(gEnemies[i].physics.vel.x > 0) {
                if(gEnemies[i].physics.pos.x + gEnemies[i].renderer.texture.width >=
                        gWidth - ENEMY_BORDER_COLLISION_X_OFFSET) {
                    vel.x = (-1) * vel.x;
                    break;
                }
            }
            else if(gEnemies[i].physics.vel.x < 0) {
                if(gEnemies[i].physics.pos.x <= 0 + ENEMY_BORDER_COLLISION_X_OFFSET) {
                    vel.x = (-1) * vel.x;
                    break;
                }
            }
        }
    }

    // Store the velocities. If any enemy is at the border of the screen,
    // change the direction of the velocity.
    for(i = 0; i < gEnemiesEnd; ++i) {
        if(gEnemies[i].exists) {
            gEnemies[i].physics.vel.x = vel.x;
        }
    }

    // Move them by dt. Remember, d = d0 + v * t
    for(i = 0; i < gEnemiesEnd; ++i) {
        if(gEnemies[i].exists) {
            gEnemies[i].physics.pos.x += gEnemies[i].physics.vel.x * dt;
        }
    }
}

/// Update the position of the enemy's projectiles.
static void moveEnemyProjectiles(float dt) {
    size_t i;
    long j;

    for(i = 0; i < gEnemyProjectilesEnd; ++i) {
        // Only move if they exist.
        if(gEnemyProjectiles[i].exists) {
            // Remember, d = d0 + v * t;
            gEnemyProjectiles[i].physics.pos.y +=
                gEnemyProjectiles[i].physics.vel.y * dt;

            // If it is outside the space, set it as nonexistent.
            if(gEnemyProjectiles[i].physics.pos.y < 0)
                gEnemyProjectiles[i].exists = false;
        }
    }

    // Go backwards and decrease gEnemyProjectilesEnd if needed.
    for(j = gEnemyProjectilesEnd - 1; j >= 0; --j) {
        if(!gEnemyProjectiles[j].exists)
            --gEnemyProjectilesEnd;
        else
            break;
    }
}

/// Detect collisions between the hero and the enemies.
static void collisionHeroEnemies() {

}

/// Detect collisions between the hero and the enemy's projectiles.
static void collisionHeroEnemyProjectiles() {
    size_t i;

    // Only test if the hero is alive.
    if(!gHero.exists)
        return;

    // Test each enemy shot.
    for(i = 0; i < gEnemyProjectilesEnd; ++i) {
        if(gEnemyProjectiles[i].exists) {
            // See if the shot is touching the hero.

            // It should be > the beginning of the hero and < the end of
            // the hero.
            if(gEnemyProjectiles[i].physics.pos.x + PROJECTILE_WIDTH <
                    gHero.physics.pos.x)
                continue;
            if(gEnemyProjectiles[i].physics.pos.x > gHero.physics.pos.x +
                    gHero.renderer.texture.width)
                continue;

            // It should be touching the hero.
            if(gEnemyProjectiles[i].physics.pos.y >
                    gHero.physics.pos.y + gHero.renderer.texture.height)
                continue;
            if(gEnemyProjectiles[i].physics.pos.y + PROJECTILE_HEIGHT <
                    gHero.physics.pos.y)
                continue;

            // If the loop gets here, we have a collision.
            gHero.exists = false;
            gHero.animation.showDeath = true;

            // Destroy the projectile that collided with the hero.
            gEnemyProjectiles[i].exists = false;

            // Fix the gEnemiesProjectilesEnd.
            while(gEnemyProjectilesEnd) {
                if(gEnemyProjectiles[gEnemyProjectilesEnd - 1].exists == false)
                    --gEnemyProjectilesEnd;
                else
                    break;
            }

            break;
        }
    }
}

/// Detect collisions between the hero and the enemy's projectiles.
static void collisionEnemiesHeroProjectile() {
    size_t i;

    // Only test if the hero projectile exists.
    if(!gHeroProjectile.exists)
        return;

    // Test each enemy.
    for(i = 0; i < gEnemiesEnd; ++i) {
        // See if the shot is touching the enemy only if it is alive.
        if(!gEnemies[i].exists)
            continue;

        // It should be > the beginning of the enemy and < the end of
        // the enemy.
        if(gHeroProjectile.physics.pos.x + PROJECTILE_WIDTH <
                gEnemies[i].physics.pos.x)
            continue;
        if(gHeroProjectile.physics.pos.x > gEnemies[i].physics.pos.x +
                gEnemies[i].renderer.texture.width)
            continue;

        // It should be touching the enemy.
        if(gHeroProjectile.physics.pos.y >
                gEnemies[i].physics.pos.y + gEnemies[i].renderer.texture.height)
            continue;
        if(gHeroProjectile.physics.pos.y + PROJECTILE_HEIGHT <
                gEnemies[i].physics.pos.y)
            continue;

        // If the loop gets here, we have a collision.
        gHeroProjectile.exists = false;

        // Add to the score.
        gHero.score += gEnemyType2Score[gEnemies[i].type] + FPS_SCORE_INFLUENCE / gFpsCount;

        // Destroy the enemy that collided with the hero.
        gEnemies[i].exists = false;
        gEnemies[i].animation.showDeath = true;

        // Set the texture as the one after the alive textures.
        gEnemies[i].animation.currentTexture = ENEMY_ALIVE_TEXTURES;

        // Fix gEnemiesEnd.
        while(gEnemiesEnd) {
            if(gEnemies[gEnemiesEnd - 1].exists == false)
                --gEnemiesEnd;
            else
                break;
        }

        // If gEnemiesEnd is 0, just end the fucking game.
        if(!gEnemiesEnd)
            endGame();

        break;
    }
}

void physicsInit() {

}

void physicsTerminate() {

}

void physicsUpdate(float dt) {
    // If the hero is dead, wait some time and then resurrect him.
    resurrectHero();

    // Update the hero position and the hero's projectile position, update the
    // position of the enemies, the position of the enemies projectiles.
    moveHero(dt);
    moveHeroProjectile(dt);
    moveEnemies(dt);
    moveEnemyProjectiles(dt);

    // Check for collisions between the hero and the enemies, between the hero and
    // the projectiles and between the enemies and the hero's projectile.
    collisionHeroEnemies();
    collisionHeroEnemyProjectiles();
    collisionEnemiesHeroProjectile();
}
