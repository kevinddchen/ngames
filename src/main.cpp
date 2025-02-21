#include <ncurses.h>

#include "board.h"
#include "common.h"
#include "text_top.h"
#include "ui.h"


class App
{
public:
    /**
     * Create application.
     */
    App(int rows, int cols, int mines)
        : cursor_y((rows - 1) / 2),
          cursor_x((cols - 1) / 2),
          text_top(board, 1, 1),
          board(rows, cols, mines, 2, 1)
    {
    }

    /**
     * Run the application.
     */
    void run()
    {
        text_top.refresh();
        board.refresh();

        while (true) {
            wmove(board.window, cursor_y + mines::BORDER_WIDTH, cursor_x + mines::BORDER_WIDTH);
            const char key = wgetch(board.window);
            handle_keystroke(key);
        }

        endwin();
    }

    /**
     * Perform action associated with given keystroke.
     * @param key Key pressed.
     */
    void handle_keystroke(char key)
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
                text_top.refresh();
                board.refresh();
                break;
            case ' ':
                board.open(cursor_y, cursor_x);
                board.refresh();
                break;
        }
    }

    int cursor_y;
    int cursor_x;
    mines::TextTop text_top;
    mines::Board board;
};

int main(int argc, char** argv)
{
    mines::init_ncurses();

    App app(8, 10, 10);
    app.run();

    return 0;
}
