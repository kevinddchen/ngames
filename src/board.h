#pragma once

#include <vector>

namespace mines
{

using cells_t = std::vector<std::vector<uint8_t>>;

class Board
{
public:
    /**
     * Minesweeper board.
     * @param rows Number of rows.
     * @param cols Number of columns.
     * @param mines Number of mines.
     */
    Board(int rows, int cols, int mines);

    /**
     * Print board state to console.
     */
    void print() const;

    const int rows;
    const int cols;
    const int mines;
    const cells_t& getCells() const;

private:
    /* Array with shape (h, w) representing the state of each cell. */
    cells_t cells;
};

}  // namespace mines
