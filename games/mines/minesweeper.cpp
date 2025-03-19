#include <games/mines/minesweeper.hpp>

#include <games/mines/neighbors.hpp>

#include <algorithm>
#include <numeric>

#include <ctime>


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
    std::srand(time(nullptr));

    const int num_rows = is_mine_array.size();
    const int num_cols = is_mine_array.front().size();
    const int num_cells = num_rows * num_cols;

    // create list of indices
    // NOTE: we encode the pair (row, col) as a single integer: row * num_cols + col
    std::vector<int> idxs(num_cells);
    std::iota(idxs.begin(), idxs.end(), 0);

    // we draw indices at random to populate mines, removing drawn indices from
    // the list to avoid drawing duplicates. we can remove an element in O(1)
    // time by replacing it with the last element of the list. to guarantee
    // index `0` not contain a mine, we remove it from the list.
    idxs.front() = idxs.back();
    idxs.pop_back();

    assert(static_cast<int>(idxs.size()) >= num_mines);  // number of mines cannot be too large

    for (int draw = 0; draw < num_mines; ++draw) {
        // pick random index from the list
        const int idx_idx = std::rand() % idxs.size();
        const int idx = idxs[idx_idx];
        // create mine
        const int row = idx / num_cols;
        const int col = idx % num_cols;
        is_mine_array[row][col] = true;
        // remove drawn index from list
        idxs[idx_idx] = idxs.back();
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
    const int num_cols = is_mine_array.front().size();

    int count = 0;
    for (const auto& [nb_row, nb_col] : games::mines::get_neighbors(row, col, num_rows, num_cols)) {
        if (is_mine_array[nb_row][nb_col]) {
            ++count;
        }
    }
    return count;
}

}  // namespace


namespace games::mines
{

Minesweeper::Minesweeper(int rows, int cols, int mines) : rows(rows), cols(cols), mines(mines)
{
    assert(rows >= MIN_ROWS);
    assert(cols >= MIN_COLS);
    assert(mines >= MIN_MINES);

    // create empty data structures
    is_mine_array.reserve(rows);
    is_opened_array.reserve(rows);
    for (int i = 0; i < rows; ++i) {
        is_mine_array.emplace_back(cols);
        is_opened_array.emplace_back(cols);
    }

    reset();
}

bool Minesweeper::open(int row, int col, std::optional<int>& neighbor_mine_count)
{
    assert(active);                      // game must be active
    assert(0 <= row && row < rows);      // row must be valid
    assert(0 <= col && col < cols);      // col must be valid
    assert(!is_opened_array[row][col]);  // cell must not be opened

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

    neighbor_mine_count = count_neighbor_mines(is_mine_array, row, col);

    if (check_win()) {
        active = false;
    }
    return false;
}

bool Minesweeper::is_mine(int row, int col) const
{
    assert(!active);                 // game must be inactive
    assert(0 <= row && row < rows);  // row must be valid
    assert(0 <= col && col < cols);  // col must be valid
    return is_mine_array[row][col];
}

void Minesweeper::reset()
{
    // initialize data
    active = true;
    num_opened = 0;

    // initialize arrays
    for (int i = 0; i < rows; ++i) {
        std::fill(is_mine_array[i].begin(), is_mine_array[i].end(), false);
        std::fill(is_opened_array[i].begin(), is_opened_array[i].end(), false);
    }

    populate_mines(is_mine_array, mines);
}

}  // namespace games::mines
