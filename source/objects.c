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
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include "objects.h"
#include "engine.h"
#include "util.h"

Hero gHero;
Projectile gHeroProjectile;
Enemy gEnemies[MAX_ENEMIES];
size_t gEnemiesEnd;
Projectile gEnemyProjectiles[MAX_PROJECTILES];
size_t gEnemyProjectilesEnd;

/// Array that stores the ids of the enemy textures
TextureData gEnemyTextures[ENEMY_NUM_TEXTURES];

int gEnemyType2Score[] = { 80, 200, 400, 800 };

/// Array that stores the original name of the enemy textures.
char *gTexture2Name[] = { "resource/texture/1.png",
                          "resource/texture/2.png",
                          "resource/texture/3.png",
                          "resource/texture/4.png",
                          "resource/texture/5.png",
                          "resource/texture/6.png",
                          "resource/texture/7.png",
                          "resource/texture/8.png" };

/// Array that stores the original size of the enemy texture's width.
int gTexture2Width[] = { 20, 23, 23, 29, 28, 42, 45, 39 };

/// Array that stores the original size of the enemy texture's height.
int gTexture2Height[] = { 16, 16, 16, 27, 27, 38, 37, 35 };

/// Array that stores the hero's textures.
TextureData gHeroTextures[HERO_NUM_TEXTURES];

/// Array that stores the original size of the hero's explosion texture's width.
int gHeroTex2Width[] = { 25, 61, 61, 81, 90, 89};

/// Array that sores the original size of the hero's explosion textures height.
int gHeroTex2Height[] = { 31, 56, 56, 69, 69, 76};

void objectsInit() {
    size_t i, j;

    // Create the hero.
    gHero.exists = true;
    gHero.lifes = 2;
    gHero.score = 0;
    gHero.physics.pos.x = gWidth / 2;
    gHero.physics.vel.y = 0;
    gHero.physics.vel.x = 0;

    // Set up the animation textures.
    gHeroTextures[0].id = loadTexture("resource/texture/15.png");
    gHeroTextures[1].id = loadTexture("resource/texture/16.png");
    gHeroTextures[2].id = loadTexture("resource/texture/17.png");
    gHeroTextures[3].id = loadTexture("resource/texture/18.png");
    gHeroTextures[4].id = loadTexture("resource/texture/19.png");
    gHeroTextures[5].id = loadTexture("resource/texture/20.png");
    gHero.animation.textures = gHeroTextures;
    gHero.animation.numTextures = 6;
    gHero.animation.currentTexture = 0;
    gHero.animation.showDeath = false;
    gHero.animation.textureChangeRate = ANIMATION_RATE;

    // Update the hero's dimensions and positions.
    updateHeroData();

    // Create the Projectiles.
    gHeroProjectile.exists = false;
    for(i = 0; i < MAX_PROJECTILES; ++i)
        gEnemyProjectiles[i].exists = false;
    gEnemyProjectilesEnd = 0;

    // Make all enemies dead.
    for(i = 0; i < MAX_ENEMIES; ++i) {
        gEnemies[i].exists = false;
    }
    gEnemiesEnd = 0;

    // Create the enemy textures.
    for(i = 0; i < ENEMY_NUM_TEXTURES; ++i)
        gEnemyTextures[i].id = loadTexture(gTexture2Name[i]);

    // Create the enemies.
    for(i = 0; i < ENEMY_NUM_ROWS; ++i) {
        for(j = 0; j < ENEMY_NUM_COLS; ++j) {
            gEnemies[AT_ENEMY(i,j)].exists = true;
            gEnemies[AT_ENEMY(i,j)].type = BlueEnemy;
            gEnemies[AT_ENEMY(i,j)].animation.textures = gEnemyTextures;
            gEnemies[AT_ENEMY(i,j)].animation.numTextures = ENEMY_NUM_TEXTURES;
            gEnemies[AT_ENEMY(i,j)].animation.currentTexture = 0;
            gEnemies[AT_ENEMY(i,j)].physics.vel.x = ENEMY_VEL;
        }
    }
    gEnemiesEnd = AT_ENEMY(ENEMY_NUM_ROWS - 1, ENEMY_NUM_COLS - 1) + 1;

    // Set up the width and height of the textures.
    updateEnemyData();

    // Set up the initial position of the enemies.
    for(i = 0; i < ENEMY_NUM_ROWS; ++i) {
        for(j = 0; j < ENEMY_NUM_COLS; ++j) {
            gEnemies[AT_ENEMY(i,j)].renderer.texture =
                gEnemies[AT_ENEMY(i,j)].animation.textures[gEnemies[AT_ENEMY(i,j)].animation.currentTexture];
            gEnemies[AT_ENEMY(i,j)].physics.pos.x = ENEMY_X_OFFSET +
                j * (gEnemies[AT_ENEMY(i,j)].renderer.texture.width + ENEMY_X_MARGIN);
            gEnemies[AT_ENEMY(i,j)].physics.pos.y = gHeight - (ENEMY_Y_OFFSET +
                i * (gEnemies[AT_ENEMY(i,j)].renderer.texture.height + ENEMY_Y_MARGIN));
        }
    }
}

void objectsTerminate() {
    size_t i;

    // Free the hero's textures.
    freeTexture(gHero.renderer.texture.id);
    gHero.renderer.texture.id = 0;

    // Remove the hero.
    gHero.exists = false;
    gHeroProjectile.exists = false;

    // Free the enemies textures.
    for(i = 0; i < ENEMY_NUM_TEXTURES; ++i) {
        freeTexture(gEnemyTextures[i].id);
        gEnemyTextures[i].id = 0;
    }

    // Remove the enemies.
    for(i = 0; i < MAX_ENEMIES; ++i) {
        gEnemies[i].exists = false;
    }
    gEnemiesEnd = 0;

    // Remove the projectiles.
    for(i = 0; i < MAX_PROJECTILES; ++i) {
        gEnemyProjectiles[i].exists = false;
    }
    gEnemyProjectilesEnd = 0;
}

void printObjects() {
    size_t i;

    printf("Existing objects:\n");

    // Print the hero.
    if(gHero.exists)
        printf("Object: Hero\tCoordinates (x, y): (%.2f, %.2f)\t"
                "Velocity (x, y): (%.2f, %.2f)\n",
                gHero.physics.pos.x, gHero.physics.pos.y,
                gHero.physics.vel.x, gHero.physics.vel.y);

    // Print the hero's projectile.
    if(gHeroProjectile.exists) {
        printf("Object: HeroProjectile\tCoordinates (x, y): (%.2f, %.2f)\t"
                "Velocity: (x, y): (%.2f, %.2f)\n",
                gHeroProjectile.physics.pos.x, gHeroProjectile.physics.pos.y,
                gHeroProjectile.physics.vel.x, gHeroProjectile.physics.vel.y);
    }

    // Print the enemies.
    for(i = 0; i < gEnemiesEnd; ++i) {
        if(gEnemies[i].exists) {
            printf("Object: Enemy\tCoordinates (x, y): (%.2f, %.2f)\t"
                    "Velocity (x, y): (%.2f, %.2f)\n",
                    gEnemies[i].physics.pos.x, gEnemies[i].physics.pos.y,
                    gEnemies[i].physics.vel.x, gEnemies[i].physics.vel.y);
        }
    }

    // Print the enemy projectiles.
    for(i = 0; i < gEnemyProjectilesEnd; ++i) {
        if(gEnemyProjectiles[i].exists) {
            printf("Object: EnemyProjectile\tCoordinates (x, y): (%.2f, %.2f)\t"
                    "Velocity: (x, y): (%.2f, %.2f)\n",
                    gEnemyProjectiles[i].physics.pos.x, gEnemyProjectiles[i].physics.pos.y,
                    gEnemyProjectiles[i].physics.vel.x, gEnemyProjectiles[i].physics.vel.y);
        }
    }

    printf("\n");
}

bool fireEnemyShot(size_t id) {
    size_t i;

    // Traverses the projectile array and fires if find an empty slot.
    for(i = 0; i < MAX_PROJECTILES; ++i) {
        if(!gEnemyProjectiles[i].exists) {
            // Set the position.
            gEnemyProjectiles[i].physics.pos.x =
                gEnemies[id].physics.pos.x + gEnemies[id].renderer.texture.width / 2;
            gEnemyProjectiles[i].physics.pos.y =
                gEnemies[i].physics.pos.y + gEnemies[i].renderer.texture.height;

            // Set the velocity.
            gEnemyProjectiles[i].physics.vel.y = (-1) * PROJECTILE_VELOCITY;

            // Set the projectile as existent.
            gEnemyProjectiles[i].exists = true;

            // If the index of the projectile we chosen was bigger than
            // gEnemyProjectilesEnd, set it as the new end.
            if(gEnemyProjectilesEnd < i)
                gEnemyProjectilesEnd = i;

            return true;
        }
    }

    return false;
}

void updateHeroData() {
    size_t i;

    gHero.physics.pos.y = HERO_LIFE_Y_OFFSET + HERO_LIFE_HEIGHT_EQ + 10;

    // Set the animation size.
    for(i = 0; i < gHero.animation.numTextures; ++i) {
        gHero.animation.textures[i].width = OBJECT_WIDTH_EQ(gHeroTex2Width[i]);
        gHero.animation.textures[i].height = OBJECT_HEIGHT_EQ(gHeroTex2Height[i]);
    }
    gHero.renderer.texture = gHero.animation.textures[gHero.animation.currentTexture];
}

void updateEnemyData() {
    size_t i;

    // Update the textures.
    for(i = 0; i < ENEMY_NUM_TEXTURES; ++i) {
        gEnemyTextures[i].width = OBJECT_WIDTH_EQ(gTexture2Width[i]);
        gEnemyTextures[i].height = OBJECT_HEIGHT_EQ(gTexture2Height[i]);
    }
}
