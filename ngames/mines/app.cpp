#include <ngames/mines/app.hpp>

#include <cassert>


namespace ngames::mines
{

App::App(int rows, int cols, int mines)
    : cursor_y((rows - 1) / 2),
      cursor_x((cols - 1) / 2),
      text_mine_count(board, MARGIN_TOP, MARGIN_LEFT),
      board_border(rows, cols, text_mine_count.bottom(), MARGIN_LEFT),
      board(rows, cols, mines, board_border.inner_start_y(), board_border.inner_start_x(), board_border.window),
      text_end_game(board, board_border.bottom(), MARGIN_LEFT),
      text_instructions(text_end_game.bottom(), MARGIN_LEFT)
{
    keypad(board.window, true);                            // allow arrow keys
    mousemask(BUTTON1_RELEASED | BUTTON3_RELEASED, NULL);  // allow mouse
    mouseinterval(0);                                      // do not wait to distinguish clicks; more reactive interface

    // initial print
    refresh();
}

void App::refresh() const
{
    text_mine_count.refresh();
    board_border.refresh();
    board.refresh();
    text_end_game.refresh();
    text_instructions.refresh();
    doupdate();
}

void App::run()
{
    while (true) {
        wmove(board.window, cursor_y, cursor_x);
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
        event.y -= board.top();
        event.x -= board.left();

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
            if (board.toggle_flag(cursor_y, cursor_x) == 0) {
                refresh();
            }
            break;
        case ' ':  // open
            if (board.click_cell(cursor_y, cursor_x) == 0) {
                refresh();
            }
            break;
        case 'z':  // new game
            board.reset();
            refresh();
            break;
        case 'r':  // refresh
            clearok(curscr, true);
            refresh();
            break;
        case 'q':  // quit
            return false;
        default:
            break;
    }
    return true;
}

}  // namespace ngames::mines
