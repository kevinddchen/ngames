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
 * @param active True if game is active.
 */
void draw_snake(WINDOW* window, const games::snakes::Snake& snake, bool active)
{
    // draw snake body excluding head and tail
    const auto body_attr = A_BOLD;
    wattron(window, body_attr);
    for (auto it = snake.chain.begin() + 1; it != snake.chain.end() - 1; ++it) {
        const auto [row, col] = *it;
        mvwaddch(window, row, col, '@');
    }
    wattroff(window, body_attr);

    // tail is not bold
    const auto [tail_row, tail_col] = snake.chain.back();
    mvwaddch(window, tail_row, tail_col, '@');

    // head is drawn specially
    char head_char;
    switch (snake.direction) {
        case games::snakes::Direction::up:
            head_char = '^';
            break;
        case games::snakes::Direction::down:
            head_char = 'v';
            break;
        case games::snakes::Direction::left:
            head_char = '<';
            break;
        case games::snakes::Direction::right:
            head_char = '>';
            break;
    }
    const auto [head_row, head_col] = snake.chain.front();
    auto head_attr = A_BOLD;
    // if game end, make snake head flash red
    if (!active) {
        head_attr |= A_BLINK | COLOR_PAIR(games::snakes::COLOR_PAIR_COLLISION);
    }
    wattron(window, head_attr);
    mvwaddch(window, head_row, head_col, head_char);
    wattroff(window, head_attr);
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
      active(true),
      score(0)
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
    draw_snake(window, snake, active);
    draw_apple(window, apple.first, apple.second);
    wnoutrefresh(window);
}

void Board::tick()
{
    // if collision, the game ends
    if (check_collision()) {
        active = false;
        return;
    }
    // otherwise, move the snake forwards
    const bool grow_snake = snake.next_head() == apple;
    snake.step(grow_snake);
    if (grow_snake) {
        apple = find_unoccupied();
        ++score;
    }
}

int Board::set_snake_direction(Direction dir)
{
    if (!active) {
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
    const int idx_idx = std::rand() % empty_idxs.size();
    const int idx = empty_idxs[idx_idx];
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
    // check collision with itself.
    // we exclude the snake tail since it will move away in time.
    for (auto it = snake.chain.begin(); it != snake.chain.end() - 1; ++it) {
        if (next == *it) {
            return true;
        }
    }
    return false;
}

}  // namespace games::snakes
