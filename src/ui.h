#pragma once

#include <ncurses.h>

#include "board.h"

namespace mines
{

class UserInterface
{
public:
    /**
     * Viewer and controller for Minesweeper board.
     * @param board Board instance.
     */
    UserInterface(Board& board);

    /**
     * Run the application.
     */
    void run();

private:
    /**
     * Print or update the board viewed by the user.
     */
    void print_board() const;

    /**
     * Perform action associated with given keystroke.
     * @param key Key pressed.
     */
    void handle_keystroke(char key);

    int cursor_y;
    int cursor_x;
    Board& board;
    WINDOW* board_win;
};

}  // namespace mines
