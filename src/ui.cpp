#include <ncurses.h>

#include "common.h"

#include "ui.h"

namespace
{

// 1 char padding to window due to border
constexpr int PAD = 1;

/**
 * Convert cell state to printable character.
 * @param board Game board.
 * @param row Cell row.
 * @param col Cell col.
 */
chtype cell_to_char(const mines::Board& board, int row, int col)
{
    // if flagged, print flag
    if (board.is_flagged(row, col)) {
        return 'F';
    }
    // if not opened, print square
    if (!(board.is_opened(row, col))) {
        return '#';
    }
    // if known mine, print 'X'
    if (board.is_known_mine(row, col)) {
        return 'X';
    }
    // otherwise, empty space. print number of neighboring mines
    const int neighbor_mines = board.get_neighbor_mine_count(row, col);
    if (neighbor_mines == 0) {
        return ' ';
    } else {
        // convert digit (as int) to char
        return neighbor_mines + '0';
    }
}

}  // namespace


namespace mines
{

UserInterface::UserInterface(Board& board)
    : cursor_y((board.rows - 1) / 2),
      cursor_x((board.cols - 1) / 2),
      board(board)
{
    initscr();
    cbreak();
    noecho();

    // create window with 1 char padding for the border
    board_win = newwin(board.rows + 2 * PAD, board.cols + 2 * PAD, 1, 1);
    box(board_win, 0, 0);
}

void UserInterface::run()
{
    // initial print of the board
    print_board();

    while (true) {
        wmove(board_win, cursor_y + PAD, cursor_x + PAD);
        const char key = wgetch(board_win);
        handle_keystroke(key);
    }
    endwin();
}

void UserInterface::print_board() const
{
    for (int row = 0; row < board.rows; ++row) {
        wmove(board_win, row + PAD, PAD);
        for (int col = 0; col < board.cols; ++col) {
            waddch(board_win, cell_to_char(board, row, col));
        }
    }
    wrefresh(board_win);
}

void UserInterface::handle_keystroke(char key)
{
    switch (key) {
        case 'h':
            if (cursor_x > 0) {
                --cursor_x;
            }
            break;
        case 'j':
            if (cursor_y < board.rows - 1) {
                ++cursor_y;
            }
            break;
        case 'k':
            if (cursor_y > 0) {
                --cursor_y;
            }
            break;
        case 'l':
            if (cursor_x < board.cols - 1) {
                ++cursor_x;
            }
            break;
        case 'f':
            board.toggle_flag(cursor_y, cursor_x);
            print_board();
            break;
        case ' ':
            board.open(cursor_y, cursor_x);
            print_board();
            break;
    }
}

}  // namespace mines
