#include <ngames/blockade/text_end_game.hpp>


namespace ngames::blockade
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
        case Board::State::win_one: {
            constexpr auto attr = A_BOLD;
            wattron(window, attr);
            mvwprintw(window, 0, 0, "PLAYER ONE WINS!");
            wattroff(window, attr);
            break;
        }
        case Board::State::win_two: {
            constexpr auto attr = A_BOLD;
            wattron(window, attr);
            mvwprintw(window, 0, 0, "PLAYER TWO WINS!");
            wattroff(window, attr);
            break;
        }
        case Board::State::tie: {
            constexpr auto attr = A_BOLD;
            wattron(window, attr);
            mvwprintw(window, 0, 0, "TIE...");
            wattroff(window, attr);
            break;
        }
    }
    wnoutrefresh(window);
}

}  // namespace ngames::blockade
