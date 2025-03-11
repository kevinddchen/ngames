#pragma once

#include <ncurses.h>


namespace games
{

/**
 * Initialize ncurses.
 */
inline void init_ncurses()
{
    initscr();
    cbreak();
    noecho();

    start_color();
}

}  // namespace games
