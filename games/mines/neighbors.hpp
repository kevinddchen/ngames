#pragma once

#include <array>
#include <vector>


namespace games::mines
{

/**
 * Convenience function for iterating the neighbors of a cell.
 * @param row Cell row.
 * @param col Cell col.
 * @param num_rows Number of rows.
 * @param num_cols Number of columns.
 * @returns List of (nb_row, nb_col).
 */
inline std::vector<std::pair<int, int>> get_neighbors(int row, int col, int num_rows, int num_cols)
{
    std::array<std::pair<int, int>, 8> neighbor_candidates;
    neighbor_candidates[0] = {row - 1, col - 1};
    neighbor_candidates[1] = {row - 1, col};
    neighbor_candidates[2] = {row - 1, col + 1};
    neighbor_candidates[3] = {row, col - 1};
    neighbor_candidates[4] = {row, col + 1};
    neighbor_candidates[5] = {row + 1, col - 1};
    neighbor_candidates[6] = {row + 1, col};
    neighbor_candidates[7] = {row + 1, col + 1};

    // filter out those outside the bounds
    std::vector<std::pair<int, int>> neighbors;
    for (auto& nb : neighbor_candidates) {
        if (nb.first >= 0 && nb.first < num_rows && nb.second >= 0 && nb.second < num_cols) {
            neighbors.push_back(std::move(nb));
        }
    }

    return neighbors;
}

}  // namespace games::mines
