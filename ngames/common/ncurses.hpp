#pragma once

#include <ncurses.h>


namespace ngames
{

constexpr short COLOR_GREY = 8;

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
}

/**
 * End ncurses.
 */
inline void end_ncurses()
{
    endwin();
}

}  // namespace ngames
