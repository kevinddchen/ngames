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
    keypad(board.window, true);                            // Allow arrow keys
    mousemask(BUTTON1_RELEASED | BUTTON3_RELEASED, NULL);  // Allow mouse

    mouseinterval(0);  // Do not wait to distinguish clicks; more reactive interface

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
}

bool App::handle_keystroke(int key)
{
    // handle mouse event
    if (key == KEY_MOUSE) {
        MEVENT event;
        if (getmouse(&event) != OK) {
            return true;
        }
        // convert to window coordinates
        event.y -= BORDER_WIDTH + board.top();
        event.x -= BORDER_WIDTH + board.left();

        if (event.y < 0 || event.y > board.rows - 1 || event.x < 0 || event.x > board.cols - 1) {
            // mouse event outside of window
            return true;
        }

        // move cursor to mouse
        cursor_y = event.y;
        cursor_x = event.x;

        if (event.bstate & BUTTON1_RELEASED) {
            // left-click opens cell, i.e. same as space
            key = ' ';
        } else if (event.bstate & BUTTON3_RELEASED) {
            // right-click toggles flag i.e. same as 'f'
            key = 'f';
        }
    }

    // handle keystroke
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
        case 'f':  // flag
            board.toggle_flag(cursor_y, cursor_x);
            text_mine_count.refresh();
            board.refresh();
            break;
        case ' ':  // open
            board.click_cell(cursor_y, cursor_x);
            board.refresh();
            text_end_game.refresh();
            break;
        case 'z':  // new game
            board.reset();
            // also do actions below
        case 'r':  // refresh
            text_mine_count.refresh();
            board.refresh();
            text_end_game.refresh();
            text_instructions.refresh();
            break;
        case 'q':  // quit
            return false;
    }
    return true;
}

}  // namespace mines
