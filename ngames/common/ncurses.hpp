#pragma once

#include <ncurses.h>


namespace ngames
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

}  // namespace ngames
