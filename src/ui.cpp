#include <string>

#include <ncurses.h>

#include "board.h"
#include "common.h"

#include "ui.h"

namespace
{

// 1 char padding to window due to border
constexpr int PAD = 1;

/**
 * Convert cell state to printable character.
 * @param cell Cell state.
 */
chtype cell_to_char(mines::cell_t cell)
{
    // if flagged, print flag
    if (mines::is_flagged(cell)) {
        return 'F';
    }
    // if not opened, print square
    if (!(mines::is_opened(cell))) {
        return '#';
    }
    // if mine, print 'X'
    if (mines::is_mine(cell)) {
        return 'X';
    }
    // otherwise, print empty space
    // TODO: print number of adjacent mines
    return ' ';
}

}  // namespace


namespace mines
{

UserInterface::UserInterface(Board& board) : cursor_y(0), cursor_x(0), board(board)
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
    const auto& cells = board.get_cells();
    for (int row = 0; row < board.rows; ++row) {
        wmove(board_win, row + PAD, PAD);
        for (auto cell : cells[row]) {
            waddch(board_win, cell_to_char(cell));
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
