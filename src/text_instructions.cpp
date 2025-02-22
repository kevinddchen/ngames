#include "common.h"

#include "text_instructions.h"


namespace mines
{

TextInstructions::TextInstructions(int start_y, int start_x) : Component(newwin(6, 16, start_y, start_x)) {}

void TextInstructions::refresh() const
{
    const auto attr = COLOR_PAIR(COLOR_PAIR_INSTRUCTIONS);
    wattron(window, attr);
    mvwprintw(window, 0, 0, "  h: move left");
    mvwprintw(window, 1, 0, "  j: move down");
    mvwprintw(window, 2, 0, "  k: move up");
    mvwprintw(window, 3, 0, "  l: move left");
    mvwprintw(window, 4, 0, "  f: place flag");
    mvwprintw(window, 5, 0, "' ': open cell");
    wattroff(window, attr);
    wrefresh(window);
}

}  // namespace mines
