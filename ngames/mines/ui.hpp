#pragma once

#include <ncurses.h>


namespace ngames::mines
{

// New grey color
constexpr short COLOR_GREY = 8;  // new color id

// Color pair for mistakes
constexpr short COLOR_PAIR_MISTAKE = 9;  // new color pair id
// Color pair for unopened cell
constexpr short COLOR_PAIR_UNOPENED = 8;  // use same color as cell 8, i.e. grey text
// Color pair for winning text
constexpr short COLOR_PAIR_WIN = 2;  // use same color as cell 2, i.e. green text
// Color pair for losing text
constexpr short COLOR_PAIR_LOSS = 3;  // use same color as cell 3, i.e. red text
// Color pair for instructions
constexpr short COLOR_PAIR_INSTRUCTIONS = 8;  // use same color as cell 8, i.e. grey text

/**
 * Initialize custom colors for Minesweeper.
 */
inline void init_colors()
{
    start_color();

    // define grey color
    init_color(COLOR_GREY, 500, 500, 500);

    // define color pairs for cell numbers
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    init_pair(8, COLOR_GREY, COLOR_BLACK);

    // define color pair for mistakes
    init_pair(COLOR_PAIR_MISTAKE, COLOR_WHITE, COLOR_RED);
};

}  // namespace ngames::mines
