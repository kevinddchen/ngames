#include "common.h"

#include "text_top.h"


namespace mines
{

TextTop::TextTop(const Board& board, int start_y, int start_x) : window(newwin(1, 10, start_y, start_x)), board(board)
{
}

void TextTop::refresh() const
{
    mvwprintw(window, 0, 0, "MINES: %3d", board.mines - board.get_num_flags());
    wrefresh(window);
}

}  // namespace mines
