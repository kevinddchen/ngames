#pragma once


namespace mines
{

// Window border width, in number of chars
constexpr int BORDER_WIDTH = 1;

// Top margin, in number of chars
constexpr int MARGIN_TOP = 1;

// Left margin, in number of chars
constexpr int MARGIN_LEFT = 1;

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
