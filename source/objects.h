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

#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdbool.h>
#include <stdlib.h>
#include "component/ai.h"
#include "component/animation.h"
#include "component/input.h"
#include "component/physics.h"
#include "component/renderer.h"
#include "system/renderer.h"

/** Maximum number of enemies. **/
#define MAX_ENEMIES 70

/** Maximum number of projectiles. **/
#define MAX_PROJECTILES 100

/** Projectile velocity. **/
#define PROJECTILE_VELOCITY 0.33

/// Represents the projetile's width.
#define PROJECTILE_WIDTH 3

/// Represents the projectile's height.
#define PROJECTILE_HEIGHT 10

/// Rate at which hero and enemies change textures, in frames.
#define ANIMATION_RATE 15

/** Number of hero's textures. **/
#define HERO_NUM_TEXTURES 6

/** Hero resurrect delay, in frames. **/
#define HERO_RESURRECT_DELAY 180

/** Hero's velocity eq, given his x position and the mouse's x position.. **/
#define HERO_VEL_EQ(x, xpos) (((xpos) - (x)) / 102)

/// Enemy velocity.
#define ENEMY_VEL 0.04

/**
 * This represents the number of times the enemy fires, given the number
 * of possible chances.
 **/
#define ENEMY_FIRE_SELECT_CHANCE 6

/**  This represents the number of possibilities to fire the shot. **/
#define ENEMY_FIRE_TOTAL_CHANCE 2950

// Number of enemy types.
#define ENEMY_NUM_TYPES 4

/// Number of enemy rows.
#define ENEMY_NUM_ROWS ENEMY_NUM_TYPES

/// Number of enemy columns.
#define ENEMY_NUM_COLS 12

/// Number of enemy textures to animate.
#define ENEMY_NUM_TEXTURES 8

/// Number of alive textures.
#define ENEMY_ALIVE_TEXTURES 3

/// Initial X offset of the enemies.
#define ENEMY_X_OFFSET 100

/// Border collision offset.
#define ENEMY_BORDER_COLLISION_X_OFFSET 10

/// Y offset of the enemies.
#define ENEMY_Y_OFFSET 120

/// X margin for the enemies.
#define ENEMY_X_MARGIN 10

/// Y margin for the enemies.
#define ENEMY_Y_MARGIN 10

/// Used when iterating through enemies.
#define AT_ENEMY(i, j) AT(i, ENEMY_NUM_COLS, j)

/**
 * Our hero.
 ***/
typedef struct Hero
{
    /** If the hero exists. **/
    bool exists;

    /** Number of lifes the hero has (except the current if he exists). **/
    int lifes;

    /** Hero's score. **/
    int score;

    /** Animation component. **/
    AnimationComponent animation;

    /** Input component. **/
    InputComponent input;

    /** Physics component. **/
    PhysicsComponent physics;

    /** Renderer component. **/
    RendererComponent renderer;
} Hero;

/**
 * Enemy type.
 **/
typedef enum EnemyType
{
    BlueEnemy,
    PurpleEnemy,
    RedEnemy,
    YellowEnemy
} EnemyType;

/// Array that converts between enemy type and score.
extern int gEnemyType2Score[ENEMY_NUM_TYPES];

/**
 * Our enemies.
 **/
typedef struct Enemy
{
    /** If the enemy exists. **/
    bool exists;

    /** Type of the enemy. **/
    EnemyType type;

    /** AI component. **/
    AiComponent ai;

    /** Animation component. **/
    AnimationComponent animation;

    /** Physics component. **/
    PhysicsComponent physics;

    /** Renderer component. **/
    RendererComponent renderer;
} Enemy;

/**
 * Projectiles.
 **/
typedef struct Projectile
{
    /** If the projectile exists. **/
    bool exists;

    /** Physics component. **/
    PhysicsComponent physics;
} Projectile;


/** Hero variable. **/
extern Hero gHero;

/** Hero projectile. **/
extern Projectile gHeroProjectile;

/** Enemy array. **/
extern Enemy gEnemies[MAX_ENEMIES];

/**
 * Position right after the last enemy in the array.
 * If 0 the array is empty.
 **/
extern size_t gEnemiesEnd;

/** Enemy projectile array. **/
extern Projectile gEnemyProjectiles[MAX_PROJECTILES];

/**
 * Position right after the last projectile in the array.
 * If 0 the array is empty.
 **/
extern size_t gEnemyProjectilesEnd;

/**
 * Inits the object data.
 **/
void objectsInit();

/**
 * Destroys the object data.
 **/
void objectsTerminate();

/**
 * Prints the existent objects to stdout.
 **/
void printObjects();

/**
 * Fires an enemy shot given the id of the enemy.
 * @param id The id of the enemy that fired the shot.
 * @return If the shot was successfully fired or not.
 **/
bool fireEnemyShot(size_t id);

/**
 * Updates the hero's variable data.
 **/
void updateHeroData();

/**
 * Updates the enemies variable data.
 **/
void updateEnemyData();

#endif /* !OBJECTS_H */
