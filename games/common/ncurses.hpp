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
}

/**
 * End ncurses.
 */
inline void end_ncurses()
{
    endwin();
}

}  // namespace games
