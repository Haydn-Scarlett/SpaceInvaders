#pragma once


/*! \file Constants.h
@brief   Constants that are used throughout the game.
@details Add any new constants to this file.
*/

/**< The window height multiplier. Defines how wide the gameplay window is. */
constexpr float GAMEPLAY_HEIGHT = 0.8f;
//constexpr float GRAVITY = 0.5f;
//constexpr float GRAVITY = 1.1f;
constexpr float GRAVITY = 2.f;

/* max size for arrays*/
constexpr int MAX_ALIENS = 55;
constexpr int MAX_LASERS = 10;
constexpr int MAX_ALIEN_LASERS = 4;
constexpr int MAX_WALL_BLOCKS = 144;
constexpr int NUM_HIGH_SCORES = 10;