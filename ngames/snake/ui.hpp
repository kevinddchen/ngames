#pragma once

#include <ncurses.h>


namespace ngames::snake
{

constexpr short COLOR_PAIR_APPLE = 1;
constexpr short COLOR_PAIR_COLLISION = 2;

/**
 * Initialize custom colors for Snakes.
 */
inline void init_colors()
{
    start_color();

    // define color pairs
    init_pair(COLOR_PAIR_APPLE, COLOR_RED, COLOR_BLACK);
    init_pair(COLOR_PAIR_COLLISION, COLOR_WHITE, COLOR_RED);
};

}  // namespace ngames::snake
