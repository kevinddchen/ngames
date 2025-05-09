#include <ngames/blockade/text_instructions.hpp>

#include <ngames/blockade/ui.hpp>


namespace ngames::blockade
{

TextInstructions::TextInstructions(int start_y, int start_x)
    : Component(newwin(TextInstructions::HEIGHT, TextInstructions::WIDTH, start_y, start_x))
{
}

void TextInstructions::refresh() const
{
    werase(window);
    constexpr auto attr = COLOR_PAIR(COLOR_PAIR_INSTRUCTIONS);
    wattron(window, attr);
    mvwprintw(window, 0, 0, "move            wasd / arrow keys");
    mvwprintw(window, 1, 0, "refresh ui      r");
    mvwprintw(window, 2, 0, "new game        z");
    mvwprintw(window, 3, 0, "quit            q");
    wattroff(window, attr);
    wnoutrefresh(window);
}

}  // namespace ngames::blockade
