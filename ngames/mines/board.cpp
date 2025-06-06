#include <ngames/mines/board.hpp>

#include <ngames/mines/neighbors.hpp>
#include <ngames/mines/ui.hpp>

#include <algorithm>

#include <cassert>


namespace ngames::mines
{

Board::Board(int rows, int cols, int mines, int start_y, int start_x, WINDOW* border_window)
    : Component(subwin(border_window, rows, cols, start_y, start_x)),
      rows(rows),
      cols(cols),
      mines(mines),
      game(rows, cols, mines)
{
    // create empty data structures
    is_known_mine_array.reserve(rows);
    is_opened_array.reserve(rows);
    is_flagged_array.reserve(rows);
    neighbor_mine_counts.reserve(rows);
    for (int i = 0; i < rows; ++i) {
        is_known_mine_array.emplace_back(cols);
        is_opened_array.emplace_back(cols);
        is_flagged_array.emplace_back(cols);
        neighbor_mine_counts.emplace_back(cols);
    }

    reset();
}

void Board::reset()
{
    // reset the game
    game.reset();

    // initialize data
    state = State::active;
    num_opened = 0;
    num_flags = 0;
    last_opened = std::nullopt;

    // initialize arrays
    for (int i = 0; i < rows; ++i) {
        std::fill(is_known_mine_array[i].begin(), is_known_mine_array[i].end(), false);
        std::fill(is_opened_array[i].begin(), is_opened_array[i].end(), false);
        std::fill(is_flagged_array[i].begin(), is_flagged_array[i].end(), false);
        std::fill(neighbor_mine_counts[i].begin(), neighbor_mine_counts[i].end(), UNSET_NEIGHBOR_MINE_COUNT);
    }
}

void Board::refresh() const
{
    werase(window);
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            print_cell(row, col);
        }
    }
    wnoutrefresh(window);
}

void Board::print_cell(int row, int col) const
{
    wmove(window, row, col);
    if (is_flagged(row, col)) {
        auto attr = A_BOLD;
        // if game ended and flag is incorrect, use red background and blink
        if (state != State::active && !is_known_mine(row, col)) {
            attr |= A_BLINK | COLOR_PAIR(COLOR_PAIR_MISTAKE);
        }
        wattron(window, attr);
        waddch(window, 'F');
        wattroff(window, attr);
        return;
    }
    if (is_known_mine(row, col)) {
        auto attr = A_BOLD;
        // if last click, use red background and blink
        if (last_opened.has_value() && row == last_opened->first && col == last_opened->second) {
            attr |= A_BLINK | COLOR_PAIR(COLOR_PAIR_MISTAKE);
        }
        wattron(window, attr);
        waddch(window, '*');
        wattroff(window, attr);
        return;
    }
    if (!is_opened(row, col)) {
        constexpr auto attr = COLOR_PAIR(COLOR_PAIR_UNOPENED);
        wattron(window, attr);
        waddch(window, '#');
        wattroff(window, attr);
        return;
    }
    // otherwise, empty cell. print number of neighboring mines
    const int neighbor_mines = get_neighbor_mine_count(row, col);
    if (neighbor_mines != 0) {
        const char digit = static_cast<char>(neighbor_mines) + '0';
        const auto attr = COLOR_PAIR(neighbor_mines);
        wattron(window, attr);
        waddch(window, digit);
        wattroff(window, attr);
    }
}

int Board::click_cell(int row, int col)
{
    if (state != State::active) {
        return 1;
    } else if (is_flagged(row, col)) {
        return 3;
    } else if (!is_opened(row, col)) {
        open(row, col);
    } else if (can_chord(row, col)) {
        open_neighbors(row, col);
    } else {
        return 2;
    }
    return 0;
}

void Board::open(int row, int col)
{
    // interact with backend
    int neighbor_mine_count = UNSET_NEIGHBOR_MINE_COUNT;  // this is set if `is_mine` is false
    const bool is_mine = game.open(row, col, neighbor_mine_count);

    // update state
    is_opened_array[row][col] = true;
    ++num_opened;
    last_opened = {row, col};

    // check if lost
    if (is_mine) {
        state = State::lose;
        populate_known_mine_array();
        return;
    }

    assert(neighbor_mine_count != UNSET_NEIGHBOR_MINE_COUNT);
    neighbor_mine_counts[row][col] = neighbor_mine_count;

    if (check_win()) {
        state = State::win;
        populate_known_mine_array();
        return;
    }

    // if no neighboring mines, recursively open all neighboring cells
    if (neighbor_mine_count == 0) {
        open_neighbors(row, col);
    }
}

void Board::open_neighbors(int row, int col)
{
    for (const auto& [nb_row, nb_col] : get_neighbors(row, col, rows, cols)) {
        if (can_open(nb_row, nb_col)) {
            open(nb_row, nb_col);
        }
    }
}

int Board::toggle_flag(int row, int col)
{
    if (state != State::active) {
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

int Board::count_neighbor_flags(int row, int col) const
{
    int count = 0;
    for (const auto& [nb_row, nb_col] : get_neighbors(row, col, rows, cols)) {
        if (is_flagged(nb_row, nb_col)) {
            ++count;
        }
    }
    return count;
}

int Board::count_neighbor_unopened(int row, int col) const
{
    int count = 0;
    for (const auto& [nb_row, nb_col] : get_neighbors(row, col, rows, cols)) {
        if (!is_opened(nb_row, nb_col)) {
            ++count;
        }
    }
    return count;
}

void Board::populate_known_mine_array()
{
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            is_known_mine_array[row][col] = game.is_mine(row, col);
        }
    }
}

}  // namespace ngames::mines
