#pragma once


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
void init_ncurses();

}  // namespace mines
