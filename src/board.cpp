#include "common.h"

#include "board.h"


namespace mines
{

Board::Board(int rows, int cols, int mines)
    : rows(rows),
      cols(cols),
      mines(mines),
      game(rows, cols, mines),
      active(true)
{
    // create empty data structures
    is_known_mine_array.reserve(rows);
    is_opened_array.reserve(rows);
    is_flagged_array.reserve(rows);
    neighbor_mine_counts.reserve(rows);
    for (int i = 0; i < rows; ++i) {
        is_known_mine_array.emplace_back(cols, false);
        is_opened_array.emplace_back(cols, false);
        is_flagged_array.emplace_back(cols, false);
        neighbor_mine_counts.emplace_back(cols, -1);  // sentinel value for unset value
    }
}

int Board::open(int row, int col)
{
    if (!active) {
        return 1;
    } else if (is_opened(row, col)) {
        return 2;
    } else if (is_flagged(row, col)) {
        return 3;
    }

    // interact with backend
    bool is_mine;
    int neighbor_mine_count;
    const int retval = game.open(row, col, is_mine, neighbor_mine_count);
    assert(retval == 0);

    is_opened_array[row][col] = true;
    if (is_mine) {
        is_known_mine_array[row][col] = true;
        active = false;  // game has ended once a mine has been opened
    } else {
        neighbor_mine_counts[row][col] = neighbor_mine_count;
    }

    // if no neighboring mines, recursively open all neighboring cells
    if (neighbor_mine_count == 0) {
        for (int dy : {-1, 0, 1}) {
            for (int dx : {-1, 0, 1}) {
                // skip case where not actually neighbor
                if (dy == 0 && dx == 0) {
                    continue;
                }
                const int nb_row = row + dy;
                const int nb_col = col + dx;
                // check bounds
                if (nb_row < 0 || nb_row >= rows || nb_col < 0 || nb_col >= cols) {
                    continue;
                }
                open(nb_row, nb_col);
            }
        }
    }
    return 0;
}

int Board::toggle_flag(int row, int col)
{
    if (!active) {
        return 1;
    } else if (is_opened(row, col)) {
        return 2;
    }

    is_flagged_array[row][col] = !is_flagged_array[row][col];
    return 0;
}

}  // namespace mines
