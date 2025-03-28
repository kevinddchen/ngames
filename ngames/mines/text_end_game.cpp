#include <ngames/mines/text_end_game.hpp>

#include <ngames/mines/ui.hpp>


namespace ngames::mines
{

TextEndGame::TextEndGame(const Board& board, int start_y, int start_x)
    : Component(newwin(TextEndGame::HEIGHT, TextEndGame::WIDTH, start_y, start_x)),
      board(board)
{
}

void TextEndGame::refresh() const
{
    werase(window);
    switch (board.get_state()) {
        case Board::State::active:
            break;
        case Board::State::win: {
            const auto attr = A_BOLD | COLOR_PAIR(COLOR_PAIR_WIN);
            wattron(window, attr);
            mvwprintw(window, 0, 0, "YOU HAVE WON!");
            wattroff(window, attr);
            break;
        }
        case Board::State::lose: {
            const auto attr = A_BOLD | COLOR_PAIR(COLOR_PAIR_LOSS);
            wattron(window, attr);
            mvwprintw(window, 0, 0, "YOU HAVE LOST...");
            wattroff(window, attr);
            break;
        }
    }
    wnoutrefresh(window);
}

}  // namespace ngames::mines
