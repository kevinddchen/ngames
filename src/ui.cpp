#include <ncurses.h>

#include "common.h"

#include "ui.h"

namespace
{

// 1 char padding to window due to border
constexpr int PAD = 1;

// new grey color macro
constexpr short COLOR_GREY = 8;

// color pair for mines
constexpr short COLOR_PAIR_MINES = 9;

// color pair for unopened cell
constexpr short COLOR_PAIR_UNOPENED = 8;  // grey

/**
 * Setup ncurses colors.
 */
void setup_colors()
{
    start_color();

    // define grey color
    init_color(COLOR_GREY, 500, 500, 500);

    // color pairs for cell numbers
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    init_pair(8, COLOR_GREY, COLOR_BLACK);

    // color pair for mines
    init_pair(COLOR_PAIR_MINES, COLOR_WHITE, COLOR_RED);
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

    setup_colors();

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

void UserInterface::print_cell(int row, int col) const
{
    // if known mine, print 'X'
    if (board.is_known_mine(row, col)) {
        wattron(board_win, A_BOLD | A_BLINK | COLOR_PAIR(COLOR_PAIR_MINES));
        waddch(board_win, '*');
        wattroff(board_win, A_BOLD | A_BLINK | COLOR_PAIR(COLOR_PAIR_MINES));
        return;
    }
    // if flagged, print flag
    if (board.is_flagged(row, col)) {
        wattron(board_win, A_BOLD);
        waddch(board_win, 'F');
        wattroff(board_win, A_BOLD);
        return;
    }
    // if not opened, print opaque square
    if (!(board.is_opened(row, col))) {
        wattron(board_win, COLOR_PAIR(COLOR_PAIR_UNOPENED));
        waddch(board_win, '#');
        wattroff(board_win, COLOR_PAIR(COLOR_PAIR_UNOPENED));
        return;
    }
    // otherwise, empty cell. print number of neighboring mines
    const int neighbor_mines = board.get_neighbor_mine_count(row, col);
    if (neighbor_mines == 0) {
        waddch(board_win, ' ');
        return;
    } else {
        // convert digit (as int) to char
        const char digit = neighbor_mines + '0';
        wattron(board_win, COLOR_PAIR(neighbor_mines));
        waddch(board_win, digit);
        wattroff(board_win, COLOR_PAIR(neighbor_mines));
        return;
    }
}

void UserInterface::print_board() const
{
    for (int row = 0; row < board.rows; ++row) {
        wmove(board_win, row + PAD, PAD);
        for (int col = 0; col < board.cols; ++col) {
            print_cell(row, col);
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
