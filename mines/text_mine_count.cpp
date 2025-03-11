#include <mines/text_mine_count.hpp>

#include <mines/common.hpp>


namespace mines
{

TextMineCount::TextMineCount(const Board& board, int start_y, int start_x)
    : Component(newwin(TextMineCount::HEIGHT, TextMineCount::WIDTH, start_y, start_x)),
      board(board)
{
}

void TextMineCount::refresh() const
{
    mvwprintw(window, 0, 0, "MINES: %-4d", board.mines - board.get_num_flags());
    wrefresh(window);
}

}  // namespace mines
