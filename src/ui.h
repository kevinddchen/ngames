#pragma once


namespace mines
{

// Window border width, in number of chars
constexpr int BORDER_WIDTH = 1;
// Top margin, in number of chars
constexpr int MARGIN_TOP = 1;
// Left margin, in number of chars
constexpr int MARGIN_LEFT = 1;

// New grey color
constexpr short COLOR_GREY = 8;

// Color pair for mines
constexpr short COLOR_PAIR_MINES = 9;  // defined in `init_ncurses()`
// Color pair for unopened cell
constexpr short COLOR_PAIR_UNOPENED = 8;  // grey text
// Color pair for winning text
constexpr short COLOR_PAIR_WIN = 2;  // green text
// Color pair for losing text
constexpr short COLOR_PAIR_LOSS = 3;  // red text


/**
 * Initialize ncurses.
 */
void init_ncurses();

}  // namespace mines
