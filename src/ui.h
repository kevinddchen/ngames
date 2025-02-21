#pragma once

#include <ncurses.h>


namespace mines
{

// Window borders are 1 px wide
constexpr int BORDER_WIDTH = 1;

// New grey color macro
constexpr short COLOR_GREY = 8;

// Color pair for mines
constexpr short COLOR_PAIR_MINES = 9;

// Color pair for unopened cell
constexpr short COLOR_PAIR_UNOPENED = 8;  // same color as "8" cell

/**
 * Initialize ncurses.
 */
inline void init_ncurses()
{
    initscr();
    cbreak();
    noecho();

    start_color();

    // define grey color
    init_color(COLOR_GREY, 500, 500, 500);

    // color pairs for cell numbers
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    init_pair(8, COLOR_GREY, COLOR_BLACK);

    // color pair for mines
    init_pair(COLOR_PAIR_MINES, COLOR_WHITE, COLOR_RED);
}

}  // namespace mines
