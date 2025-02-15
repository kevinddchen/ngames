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
        std::vector<char> chars(board.cols);
        for (int col = 0; col < board.cols; ++col) {
            chars[col] = cells[row][col] + char('0');
        }
        std::string row_string(chars.begin(), chars.end());
        mvprintw(row, 0, row_string.c_str());
    }
}

}  // namespace


namespace mines
{

UserInterface::UserInterface(Board& board) : cursor_y(0), cursor_x(0), board(board) {}

void UserInterface::run()
{
    initscr();

    while (true) {
        print_board(board);
        move(cursor_y, cursor_x);
        refresh();
        const char key = getch();
        handle_keystroke(key);
    }
    endwin();
}

void UserInterface::handle_keystroke(char key)
{
    if (key == 'h' && cursor_x > 0) {
        --cursor_x;
    } else if (key == 'l' && cursor_x < board.cols - 1) {
        ++cursor_x;
    } else if (key == 'j' && cursor_y < board.rows - 1) {
        ++cursor_y;
    } else if (key == 'k' && cursor_y > 0) {
        --cursor_y;
    }
}

}  // namespace mines
