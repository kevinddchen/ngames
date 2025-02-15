#include <numeric>

#include "common.h"

#include "board.h"

namespace
{

/**
 * Randomly populate mines on the board.
 * @param cells Board state, initially blank.
 * @param num_mines Number of mines to create.
 */
void populate_mines(mines::cells_t& cells, int num_mines)
{
    // seed RNG with current time
    std::srand(time(0));

    const int num_rows = cells.size();
    const int num_cols = cells[0].size();
    const int num_cells = num_rows * num_cols;
    assert(num_mines <= num_cells);

    // create list of indices
    std::vector<int> idxs(num_cells);
    std::iota(idxs.begin(), idxs.end(), 0);

    // we draw indices at random to populate mines, and put drawn indices at the back of the list
    for (int num_undrawn_idxs = num_cells; num_cells - num_undrawn_idxs < num_mines; --num_undrawn_idxs) {
        // pick random element from first `num_undrawn_idxs` elements of `idxs`
        const int i = std::rand() % num_undrawn_idxs;
        const int idx = idxs[i];
        // create mine
        const int row = idx / num_cols;
        const int col = idx % num_cols;
        cells[row][col] = 1;
        // put drawn index after all undrawn indices
        idxs[i] = idxs[num_undrawn_idxs - 1];
        idxs[num_undrawn_idxs - 1] = idx;
    }
}

}  // namespace


namespace mines
{

Board::Board(int rows, int cols, int mines) : rows(rows), cols(cols), mines(mines)
{
    cells.reserve(rows);
    for (int i = 0; i < rows; ++i) {
        cells.emplace_back(cols, 0);
    }
    populate_mines(cells, mines);
}

void Board::print() const
{
    for (const auto& row : cells) {
        for (auto el : row) {
            printf("%u ", el);
        }
        printf("\n");
    }
}

const cells_t& Board::getCells() const
{
    return cells;
}

}  // namespace mines
