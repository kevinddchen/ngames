#pragma once

#include <ncurses.h>


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
// Color pair for instructions
constexpr short COLOR_PAIR_INSTRUCTIONS = 8;  // grey text

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

/**
 * Abstract base class for an interactive component.
 */
class Component
{
public:
    /**
     * Create component.
     * @param window Window displaying text for the component.
     */
    Component(WINDOW* window) : window(window) {};

    /**
     * Refresh the text viewed by the user.
     */
    virtual void refresh() const = 0;

    WINDOW* const window;
};

}  // namespace mines
