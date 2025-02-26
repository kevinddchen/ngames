#include <algorithm>
#include <numeric>
#include <stdexcept>

#include "common.h"

#include "game.h"


namespace
{

/**
 * Randomly populate mines. Cell (0, 0) is guaranteed to not contain a mine.
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

    // create list of indices
    // NOTE: we encode the pair (row, col) as a single integer: row * num_cols + col
    std::vector<int> idxs(num_cells);
    std::iota(idxs.begin(), idxs.end(), 0);

    // we draw indices at random to populate mines, removing drawn indices from
    // the list to avoid drawing duplicates. we can remove an element in O(1)
    // time by replacing it with the last element of the list. to guarantee
    // index `0` not contain a mine, we remove it from the list.
    idxs[0] = idxs[idxs.size() - 1];
    idxs.pop_back();

    assert(idxs.size() >= num_mines);  // number of mines cannot be too large

    for (int draw = 0; draw < num_mines; ++draw) {
        // pick random index from the list
        const int idx_idx = std::rand() % idxs.size();
        const int idx = idxs[idx_idx];
        // create mine
        const int row = idx / num_cols;
        const int col = idx % num_cols;
        is_mine_array[row][col] = true;
        // remove drawn index from list
        idxs[idx_idx] = idxs[idxs.size() - 1];
        idxs.pop_back();
    }

    assert(!is_mine_array[0][0]);  // sanity check (0, 0) does not contain a mine
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
            if (nb_row < 0 || nb_row >= num_rows || nb_col < 0 || nb_col >= num_cols) {
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

Game::Game(int rows, int cols, int mines) : rows(rows), cols(cols), mines(mines), active(true), num_opened(0)
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

bool Game::open(int row, int col, std::optional<int>& neighbor_mine_count)
{
    if (!active) {
        throw std::runtime_error("Game is not active");
    } else if (is_opened_array[row][col]) {
        throw std::runtime_error("Cell has already been opened");
    }

    // if first cell opened, guarantee no mine by shifting all cells down/right
    // so that (0, 0) becomes the cell just clicked on
    if (num_opened == 0) {
        std::rotate(is_mine_array.rbegin(), is_mine_array.rbegin() + row, is_mine_array.rend());
        for (auto& is_mine_row : is_mine_array) {
            std::rotate(is_mine_row.rbegin(), is_mine_row.rbegin() + col, is_mine_row.rend());
        }
    }

    // update state
    is_opened_array[row][col] = true;
    ++num_opened;

    // check if lost
    if (is_mine_array[row][col]) {
        active = false;
        return true;
    }

    // check if won
    neighbor_mine_count = count_neighbor_mines(is_mine_array, row, col);
    if (num_opened + mines == rows * cols) {  // if all non-mine cells have been opened
        active = false;
    }
    return false;
}

}  // namespace mines
