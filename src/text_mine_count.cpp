#include "common.h"

#include "text_mine_count.h"


namespace mines
{

TextMineCount::TextMineCount(const Board& board, int start_y, int start_x)
    : window(newwin(1, 16, start_y, start_x)),
      board(board)
{
}

void TextMineCount::refresh() const
{
    mvwprintw(window, 0, 0, "MINES: %-4d", board.mines - board.get_num_flags());
    wrefresh(window);
}

}  // namespace mines
