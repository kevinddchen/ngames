#include "common.h"

#include "ui.h"


namespace mines
{

void init_ncurses()
{
    initscr();
    cbreak();
    noecho();

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
}

Component::Component(WINDOW* window) : window(window) {}

Component::~Component() {}

}  // namespace mines
