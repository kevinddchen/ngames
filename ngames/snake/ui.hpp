#pragma once

#include <ncurses.h>


namespace ngames::snake
{

// New grey color
constexpr short COLOR_GREY = 8;  // new color id

// Color pair for apple
constexpr short COLOR_PAIR_APPLE = 1;
// Color pair for snake head when it collides
constexpr short COLOR_PAIR_COLLISION = 2;
// Color pair for instructions
constexpr short COLOR_PAIR_INSTRUCTIONS = 3;

/**
 * Initialize custom colors for Snakes.
 */
inline void init_colors()
{
    start_color();

    // define grey color
    init_color(COLOR_GREY, 500, 500, 500);

    // define color pairs
    init_pair(COLOR_PAIR_APPLE, COLOR_RED, COLOR_BLACK);
    init_pair(COLOR_PAIR_COLLISION, COLOR_WHITE, COLOR_RED);
    init_pair(COLOR_PAIR_INSTRUCTIONS, COLOR_GREY, COLOR_BLACK);
};

}  // namespace ngames::snake
