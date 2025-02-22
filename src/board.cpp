#include "common.h"

#include "board.h"


namespace mines
{

Board::Board(int rows, int cols, int mines, int start_y, int start_x)
    : Component(newwin(rows + 2 * BORDER_WIDTH, cols + 2 * BORDER_WIDTH, start_y, start_x)),
      rows(rows),
      cols(cols),
      mines(mines),
      game(rows, cols, mines),
      active(true),
      num_opened(0),
      num_flags(0)
{
    // create window border
    box(window, 0, 0);

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
    ++num_opened;
    if (is_mine) {
        is_known_mine_array[row][col] = true;
        active = false;  // game has ended once a mine has been opened
    } else {
        neighbor_mine_counts[row][col] = neighbor_mine_count;
        if (is_win()) {
            active = false;  // game has ended once all non-mine cells have been opened
        }
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

    if (is_flagged_array[row][col]) {
        is_flagged_array[row][col] = false;
        --num_flags;
    } else {
        is_flagged_array[row][col] = true;
        ++num_flags;
    }
    return 0;
}

void Board::refresh() const
{
    for (int row = 0; row < rows; ++row) {
        wmove(window, row + BORDER_WIDTH, BORDER_WIDTH);
        for (int col = 0; col < cols; ++col) {
            print_cell(row, col);
        }
    }
    wrefresh(window);
}

void Board::print_cell(int row, int col) const
{
    // if known mine, print '*'
    if (is_known_mine(row, col)) {
        const auto attr = A_BOLD | A_BLINK | COLOR_PAIR(COLOR_PAIR_MINES);
        wattron(window, attr);
        waddch(window, '*');
        wattroff(window, attr);
        return;
    }
    // if flagged, print flag
    if (is_flagged(row, col)) {
        const auto attr = A_BOLD;
        wattron(window, attr);
        waddch(window, 'F');
        wattroff(window, attr);
        return;
    }
    // if not opened, print opaque square
    if (!(is_opened(row, col))) {
        const auto attr = COLOR_PAIR(COLOR_PAIR_UNOPENED);
        wattron(window, attr);
        waddch(window, '#');
        wattroff(window, attr);
        return;
    }
    // otherwise, empty cell. print number of neighboring mines
    const int neighbor_mines = get_neighbor_mine_count(row, col);
    if (neighbor_mines == 0) {
        waddch(window, ' ');
        return;
    } else {
        // convert digit (as int) to char
        const auto attr = COLOR_PAIR(neighbor_mines);
        const char digit = neighbor_mines + '0';
        wattron(window, attr);
        waddch(window, digit);
        wattroff(window, attr);
        return;
    }
}

}  // namespace mines
