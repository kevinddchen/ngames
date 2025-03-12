#include <games/mines/text_end_game.hpp>

#include <games/mines/ui.hpp>


namespace games::mines
{

TextEndGame::TextEndGame(const Board& board, int start_y, int start_x)
    : Component(newwin(TextEndGame::HEIGHT, TextEndGame::WIDTH, start_y, start_x)),
      board(board)
{
}

void TextEndGame::refresh() const
{
    switch (board.get_state()) {
        case BoardState::active:
            wclear(window);
            break;
        case BoardState::win: {
            const auto attr = A_BOLD | COLOR_PAIR(COLOR_PAIR_WIN);
            wattron(window, attr);
            mvwprintw(window, 0, 0, "YOU HAVE WON!");
            wattroff(window, attr);
            break;
        }
        case BoardState::lose: {
            const auto attr = A_BOLD | COLOR_PAIR(COLOR_PAIR_LOSS);
            wattron(window, attr);
            mvwprintw(window, 0, 0, "YOU HAVE LOST...");
            wattroff(window, attr);
            break;
        }
    }
    wrefresh(window);
}

}  // namespace games::mines
