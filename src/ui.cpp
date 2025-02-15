#include <string>

#include <ncurses.h>

#include "common.h"

#include "ui.h"

namespace
{

/**
 * Print board in the window.
 */
void print_board(const mines::Board& board)
{
    const auto& cells = board.getCells();
    for (int row = 0; row < board.rows; ++row) {
        std::vector<char> chars(2 * board.cols);
        for (int col = 0; col < board.cols; ++col) {
            chars[2 * col] = cells[row][col] + char('0');
            chars[2 * col + 1] = ' ';
        }
        std::string row_string(chars.begin(), chars.end());
        mvprintw(row, 0, row_string.c_str());
    }
}

}  // namespace


namespace mines
{

UserInterface::UserInterface(Board& board) : board(board) {}

void UserInterface::run()
{
    initscr();

    print_board(board);
    refresh();
    move(0, 0);

    getch();
    endwin();
}

}  // namespace mines
