#include "common.h"

#include "text_instructions.h"


namespace mines
{

TextInstructions::TextInstructions(int start_y, int start_x) : Component(newwin(7, 24, start_y, start_x)) {}

void TextInstructions::refresh() const
{
    const auto attr = COLOR_PAIR(COLOR_PAIR_INSTRUCTIONS);
    wattron(window, attr);
    mvwprintw(window, 0, 0, " h/left: move left");
    mvwprintw(window, 1, 0, " j/down: move down");
    mvwprintw(window, 2, 0, "   k/up: move up");
    mvwprintw(window, 3, 0, "l/right: move right");
    mvwprintw(window, 4, 0, "      f: place flag");
    mvwprintw(window, 5, 0, "  space: open cell");
    mvwprintw(window, 6, 0, "      q: quit");
    wattroff(window, attr);
    wrefresh(window);
}

}  // namespace mines
