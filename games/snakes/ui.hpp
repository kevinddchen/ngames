#pragma once

#include <ncurses.h>


namespace games::snakes
{

constexpr short COLOR_PAIR_APPLE = 1;

/**
 * Initialize custom colors for Snakes.
 */
inline void init_colors()
{
    start_color();

    // define color pairs
    init_pair(COLOR_PAIR_APPLE, COLOR_RED, COLOR_BLACK);
};

}  // namespace games::snakes
