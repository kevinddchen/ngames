#include <string>

#include <ncurses.h>

#include "common.h"

#include "ui.h"

namespace
{

// 1 char padding to window due to border
constexpr int PAD = 1;

/**
 * Print board in the window.
 */
void print_board(WINDOW* win, const mines::Board& board)
{
    const auto& cells = board.getCells();
    for (int row = 0; row < board.rows; ++row) {
        wmove(win, row + PAD, PAD);
        for (auto el : cells[row]) {
            waddch(win, el + '0');
        }
    }
    wrefresh(win);
}

}  // namespace


namespace mines
{

UserInterface::UserInterface(Board& board) : cursor_y(0), cursor_x(0), board(board) {}

void UserInterface::run()
{
    initscr();
    cbreak();
    noecho();

    // create window with 1 char padding for the border
    WINDOW* board_win = newwin(board.rows + 2 * PAD, board.cols + 2 * PAD, 1, 1);
    box(board_win, 0, 0);

    print_board(board_win, board);

    while (true) {
        wmove(board_win, cursor_y + PAD, cursor_x + PAD);
        const char key = wgetch(board_win);
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
