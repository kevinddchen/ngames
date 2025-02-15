#pragma once

#include "board.h"

namespace mines
{

class UserInterface
{
public:
    /**
     * Viewer and controller for Minesweeper board.
     * @param rows Number of rows.
     * @param cols Number of columns.
     * @param mines Number of mines.
     */
    UserInterface(Board& board);

    /**
     * Run the application.
     */
    void run();

private:
    /**
     * Perform action associated with given keystroke.
     */
    void handle_keystroke(char key);

    int cursor_y;
    int cursor_x;
    Board& board;
};

}  // namespace mines
