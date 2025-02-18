#pragma once

#include <vector>


namespace mines
{

/**
 * Back-end for the Minesweeper game. Contains secret game state hidden from
 * the player, i.e. the locations of all mines.
 */
class Game
{
public:
    /**
     * Create back-end for new Minesweeper game.
     * @param rows Number of rows.
     * @param cols Number of columns.
     * @param mines Number of mines.
     */
    Game(int rows, int cols, int mines);

    /**
     * Open a cell.
     *
     * First cell opened is guaranteed to not contain a mine.
     *
     * @param row Cell row.
     * @param col Cell column.
     * @param is_mine Will be set to true if the cell contains a mine.
     * @param neighbor_mine_count If cell is not a mine, will be set to the
     * number of neighboring mines.
     *
     * @returns Return code. A non-zero value means that an error occurred and
     * the game state was not been changed. The possible error codes are
     *   1: game is inactive.
     *   2: cell has already been opened.
     */
    int open(int row, int col, bool& is_mine, int& neighbor_mine_count);

private:
    // Array with shape (rows, cols) tracking which cells contain a mine.
    std::vector<std::vector<bool>> is_mine_array;
    // Array with shape (rows, cols) tracking which cells have been opened.
    std::vector<std::vector<bool>> is_opened_array;
    // Whether the game is active.
    bool active;
    // Number of opened cells.
    int num_opened;
};

}  // namespace mines
