#include <ncurses.h>

#include "board.h"
#include "common.h"
#include "text_end_game.h"
#include "text_instructions.h"
#include "text_mine_count.h"
#include "ui.h"


namespace mines
{

class App
{
public:
    /**
     * Create application.
     * @param rows Number of rows for the Minesweeper board.
     * @param cols Number of columns for the Minesweeper board.
     * @param mines Number of mines for the Minesweeper board.
     */
    App(int rows, int cols, int mines)
        : cursor_y((rows - 1) / 2),
          cursor_x((cols - 1) / 2),
          text_mine_count(board, MARGIN_TOP, MARGIN_LEFT),        // height is 1
          board(rows, cols, mines, MARGIN_TOP + 1, MARGIN_LEFT),  // height is rows + 2 * BORDER_WIDTH
          text_end_game(board, MARGIN_TOP + 1 + rows + 2 * BORDER_WIDTH, MARGIN_LEFT),  // height is 1
          // 1 row buffer
          text_instructions(MARGIN_TOP + 3 + rows + 2 * BORDER_WIDTH, MARGIN_LEFT)
    {
    }

    /**
     * Run the application.
     */
    void run()
    {
        // Initial print
        text_mine_count.refresh();
        board.refresh();
        text_end_game.refresh();
        text_instructions.refresh();

        while (true) {
            wmove(board.window, cursor_y + BORDER_WIDTH, cursor_x + BORDER_WIDTH);
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
                text_mine_count.refresh();
                board.refresh();
                break;
            case ' ':
                board.open(cursor_y, cursor_x);
                board.refresh();
                text_end_game.refresh();
                break;
        }
    }

    // y-coordinate of cursor, relative to board window.
    int cursor_y;
    // x-coordinate of cursor, relative to board window.
    int cursor_x;

    TextMineCount text_mine_count;
    Board board;
    TextEndGame text_end_game;
    TextInstructions text_instructions;
};

}  // namespace mines


int main(int argc, char** argv)
{
    mines::init_ncurses();

    mines::App app(8, 10, 10);
    app.run();

    return 0;
}
