#include "common.h"

#include "text_instructions.h"


namespace mines
{

TextInstructions::TextInstructions(int start_y, int start_x)
    : Component(newwin(TextInstructions::HEIGHT, TextInstructions::WIDTH, start_y, start_x))
{
}

void TextInstructions::refresh() const
{
    const auto attr = COLOR_PAIR(COLOR_PAIR_INSTRUCTIONS);
    wattron(window, attr);
    mvwprintw(window, 0, 0, "hjkl / arrow keys to move");
    mvwprintw(window, 1, 0, "    f: place flag");
    mvwprintw(window, 2, 0, "space: open cell / chord");
    mvwprintw(window, 3, 0, "    r: reset");
    mvwprintw(window, 4, 0, "    q: quit");
    wattroff(window, attr);
    wrefresh(window);
}

}  // namespace mines
