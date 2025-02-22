#include "common.h"
#include "ui.h"

#include "text_end_game.h"


namespace mines
{

TextEndGame::TextEndGame(const Board& board, int start_y, int start_x)
    : window(newwin(1, 16, start_y, start_x)),
      board(board)
{
}

void TextEndGame::refresh() const
{
    // check if game has ended
    if (!board.is_active()) {
        // check if win
        if (board.is_win()) {
            wattron(window, A_BOLD | COLOR_PAIR(COLOR_PAIR_WIN));
            mvwprintw(window, 0, 0, "YOU HAVE WON!");
            wattroff(window, A_BOLD | COLOR_PAIR(COLOR_PAIR_WIN));
        } else {
            wattron(window, A_BOLD | COLOR_PAIR(COLOR_PAIR_LOSS));
            mvwprintw(window, 0, 0, "YOU HAVE LOST...");
            wattroff(window, A_BOLD | COLOR_PAIR(COLOR_PAIR_LOSS));
        }
    }
    wrefresh(window);
}

}  // namespace mines
