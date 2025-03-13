#include <games/mines/text_instructions.hpp>

#include <games/mines/ui.hpp>


namespace games::mines
{

TextInstructions::TextInstructions(int start_y, int start_x)
    : Component(newwin(TextInstructions::HEIGHT, TextInstructions::WIDTH, start_y, start_x))
{
}

void TextInstructions::refresh() const
{
    wclear(window);
    const auto attr = COLOR_PAIR(COLOR_PAIR_INSTRUCTIONS);
    wattron(window, attr);
    mvwprintw(window, 0, 0, "move cursor     hjkl / arrow keys");
    mvwprintw(window, 1, 0, "toggle flag     f / right click");
    mvwprintw(window, 2, 0, "open / chord    space / left click");
    mvwprintw(window, 3, 0, "refresh ui      r");
    mvwprintw(window, 4, 0, "new game        z");
    mvwprintw(window, 5, 0, "quit            q");
    wattroff(window, attr);
    wrefresh(window);
}

}  // namespace games::mines
