#include <games/snakes/board.hpp>

#include <games/snakes/ui.hpp>

#include <numeric>
#include <vector>

#include <ctime>


namespace
{

/**
 * Draw the snake on the window.
 * @param window Window.
 * @param snake Snake instance.
 */
void draw_snake(WINDOW* window, const games::snakes::Snake& snake)
{
    // draw snake body
    for (auto it = snake.chain.begin() + 1; it != snake.chain.end(); ++it) {
        const auto [row, col] = *it;
        mvwaddch(window, row, col, '@');
    }

    // head is drawn specially
    const auto [head_row, head_col] = snake.chain.front();
    switch (snake.direction) {
        case games::snakes::Direction::up:
            mvwaddch(window, head_row, head_col, '^');
            break;
        case games::snakes::Direction::down:
            mvwaddch(window, head_row, head_col, 'v');
            break;
        case games::snakes::Direction::left:
            mvwaddch(window, head_row, head_col, '<');
            break;
        case games::snakes::Direction::right:
            mvwaddch(window, head_row, head_col, '>');
            break;
    }
}

/**
 * Draw the apple.
 * @param window Window.
 * @param row Cell row for the apple.
 * @param col Cell column for the apple.
 */
void draw_apple(WINDOW* window, int row, int col)
{
    const auto attr = A_BOLD | COLOR_PAIR(games::snakes::COLOR_PAIR_APPLE);
    wattron(window, attr);
    mvwaddch(window, row, col, '*');
    wattroff(window, attr);
}

}  // namespace


namespace games::snakes
{

Board::Board(int rows, int cols, int start_y, int start_x, WINDOW* border_window)
    : Component(subwin(border_window, rows, cols, start_y, start_x)),
      rows(rows),
      cols(cols),
      snake(1, 1, Direction::left, 3),  // snake starts along top of board
      state(BoardState::active)
{
    assert(rows >= MIN_ROWS);
    assert(cols >= MIN_COLS);

    // check snake endpoints are inside board
    for (const auto& [row, col] : {snake.chain.front(), snake.chain.back()}) {
        assert(0 <= row && row < rows);
        assert(0 <= col && col < cols);
    }

    // start snake pointing down
    snake.direction = Direction::down;

    // initialize apple at random location
    apple = find_unoccupied();
}

void Board::refresh() const
{
    werase(window);
    draw_snake(window, snake);
    draw_apple(window, apple.first, apple.second);
    wnoutrefresh(window);
}

void Board::tick()
{
    // if collision, the game ends
    if (check_collision()) {
        state = BoardState::lose;
        return;
    }
    // otherwise, move the snake forwards
    const bool grow_snake = snake.next_head() == apple;
    snake.step(grow_snake);
    if (grow_snake) {
        apple = find_unoccupied();
    }
}

int Board::set_snake_direction(Direction dir)
{
    if (state != BoardState::active) {
        return 1;
    } else if (snake.chain.size() > 1 && snake.next_head(dir) == snake.chain[1]) {
        return 2;
    }
    snake.direction = dir;
    return 0;
}

std::pair<int, int> Board::find_unoccupied() const
{
    // seed RNG with current time
    std::srand(time(nullptr));

    // create list tracking empty cells
    // NOTE: we encode the pair (row, col) as a single index: row * num_cols + col
    std::vector<bool> empty(rows * cols, true);

    // mark cells in the snake as `false`
    for (const auto& [row, col] : snake.chain) {
        const int idx = row * cols + col;
        empty[idx] = false;
    }

    // gather a list of empty indices
    std::vector<int> empty_idxs;
    for (int idx = 0; idx < static_cast<int>(empty.size()); ++idx) {
        if (empty[idx]) {
            empty_idxs.push_back(idx);
        }
    }
    assert(empty_idxs.size() > 0);

    // draw random index
    const int idx = std::rand() % empty_idxs.size();
    const int row = idx / cols;
    const int col = idx % cols;

    return {row, col};
}

bool Board::check_collision() const
{
    const auto next = snake.next_head();
    // check collision with wall
    if (next.first < 0 || next.first >= rows || next.second < 0 || next.second >= cols) {
        return true;
    }
    // check collision with itself
    for (const auto& cell : snake.chain) {
        if (next == cell) {
            return true;
        }
    }
    return false;
}

}  // namespace games::snakes
