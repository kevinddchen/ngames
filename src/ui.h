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
    Board& board;
};

}  // namespace mines
