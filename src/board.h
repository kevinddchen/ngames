#pragma once

#include <vector>

namespace mines
{

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

    int rows;
    int cols;
    int mines;
    /* Array with shape (h, w) representing the state of each cell. */
    std::vector<std::vector<uint8_t>> cells;
};

}  // namespace mines
