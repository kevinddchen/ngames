#pragma once

#include "board.h"
#include "text_end_game.h"
#include "text_instructions.h"
#include "text_mine_count.h"


namespace mines
{

/**
 * Minesweeper application.
 */
class App
{
public:
    /**
     * Create application.
     * @param rows Number of rows for the Minesweeper board.
     * @param cols Number of columns for the Minesweeper board.
     * @param mines Number of mines for the Minesweeper board.
     */
    App(int rows, int cols, int mines);

    /**
     * Run the application.
     */
    void run();

private:
    /**
     * Perform action associated with given keystroke.
     * @param key Key pressed.
     * @returns False when we want to quit.
     */
    bool handle_keystroke(int key);

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
