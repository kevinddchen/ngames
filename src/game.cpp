#include <numeric>

#include "common.h"

#include "game.h"


namespace
{

/**
 * Randomly populate mines.
 * @param is_mine_array Array tracking which cells contain a mine, initially all false.
 * @param num_mines Number of mines to create.
 */
void populate_mines(std::vector<std::vector<bool>>& is_mine_array, int num_mines)
{
    // seed RNG with current time
    std::srand(time(0));

    const int num_rows = is_mine_array.size();
    const int num_cols = is_mine_array[0].size();
    const int num_cells = num_rows * num_cols;
    assert(num_mines <= num_cells);

    // create list of indices
    // NOTE: we encode the pair (row, col) as a single integer: row * num_cols + col
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
        is_mine_array[row][col] = true;
        // put drawn index after all undrawn indices
        idxs[i] = idxs[num_undrawn_idxs - 1];
        idxs[num_undrawn_idxs - 1] = idx;
    }
}

/**
 * Count the number of mines neighboring a cell.
 * @param is_mine_array Array tracking which cells contain a mine.
 * @param row Cell row.
 * @param col Cell col.
 */
int count_neighbor_mines(const std::vector<std::vector<bool>>& is_mine_array, int row, int col)
{
    const int num_rows = is_mine_array.size();
    const int num_cols = is_mine_array[0].size();

    int count = 0;
    for (int dy : {-1, 0, 1}) {
        for (int dx : {-1, 0, 1}) {
            // skip case where not actually neighbor
            if (dy == 0 && dx == 0) {
                continue;
            }
            const int nb_row = row + dy;
            const int nb_col = col + dx;
            // check bounds
            if (nb_row < 0 || nb_row >= num_rows || nb_col < 0 || nb_col > num_cols) {
                continue;
            }
            if (is_mine_array[nb_row][nb_col]) {
                ++count;
            }
        }
    }
    return count;
}

}  // namespace


namespace mines
{

Game::Game(int rows, int cols, int mines) : active(true)
{
    // create empty data structures
    is_mine_array.reserve(rows);
    is_opened_array.reserve(rows);
    for (int i = 0; i < rows; ++i) {
        is_mine_array.emplace_back(cols, false);
        is_opened_array.emplace_back(cols, false);
    }

    populate_mines(is_mine_array, mines);
}

int Game::open(int row, int col, bool& is_mine, int& neighbor_mine_count)
{
    if (!active) {
        return 1;
    } else if (is_opened_array[row][col]) {
        return 2;
    }

    is_opened_array[row][col] = true;
    if (is_mine_array[row][col]) {
        is_mine = true;
        active = false;  // game has ended once a mine has been opened
    } else {
        is_mine = false;
        neighbor_mine_count = count_neighbor_mines(is_mine_array, row, col);
    }
    return 0;
}

}  // namespace mines
