#include <ncurses.h>

#include "common.h"

#include "app.h"


namespace mines
{

App::App(int rows, int cols, int mines)
    : cursor_y((rows - 1) / 2),
      cursor_x((cols - 1) / 2),
      text_mine_count(board, MARGIN_TOP, MARGIN_LEFT),
      board(rows, cols, mines, text_mine_count.bottom(), MARGIN_LEFT),
      text_end_game(board, board.bottom(), MARGIN_LEFT),
      text_instructions(text_end_game.bottom(), MARGIN_LEFT)
{
    // Allow arrow keys
    keypad(board.window, true);

    // Initial print
    text_mine_count.refresh();
    board.refresh();
    text_end_game.refresh();
    text_instructions.refresh();
}

void App::run()
{
    while (true) {
        wmove(board.window, cursor_y + BORDER_WIDTH, cursor_x + BORDER_WIDTH);
        const int key = wgetch(board.window);
        if (!handle_keystroke(key)) {
            break;
        }
    }

    endwin();
}

bool App::handle_keystroke(int key)
{
    switch (key) {
        case 'h':
        case KEY_LEFT:
            if (cursor_x > 0) {
                --cursor_x;
            }
            break;
        case 'j':
        case KEY_DOWN:
            if (cursor_y < board.rows - 1) {
                ++cursor_y;
            }
            break;
        case 'k':
        case KEY_UP:
            if (cursor_y > 0) {
                --cursor_y;
            }
            break;
        case 'l':
        case KEY_RIGHT:
            if (cursor_x < board.cols - 1) {
                ++cursor_x;
            }
            break;
        case 'f':
            board.toggle_flag(cursor_y, cursor_x);
            text_mine_count.refresh();
            board.refresh();
            break;
        case ' ':
            board.click_cell(cursor_y, cursor_x);
            board.refresh();
            text_end_game.refresh();
            break;
        case 'r':
            board.reset();
            text_mine_count.refresh();
            board.refresh();
            text_end_game.refresh();
            break;
        case 'q':
            return false;
    }
    return true;
}

}  // namespace mines
