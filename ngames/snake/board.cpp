#include <ngames/snake/board.hpp>

#include <ngames/snake/ui.hpp>

#include <numeric>
#include <vector>

#include <cassert>
#include <cstdlib>
#include <ctime>


namespace
{

/**
 * Draw the snake on the window.
 * @param window Window.
 * @param snake Snake instance.
 * @param state Board state.
 */
void draw_snake(WINDOW* window, const ngames::snake::Snake& snake, ngames::snake::BoardState state)
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
        case ngames::snake::Direction::up:
            head_char = '^';
            break;
        case ngames::snake::Direction::down:
            head_char = 'v';
            break;
        case ngames::snake::Direction::left:
            head_char = '<';
            break;
        case ngames::snake::Direction::right:
            head_char = '>';
            break;
    }
    const auto [head_row, head_col] = snake.chain.front();
    auto head_attr = A_BOLD;
    // if game lost, make snake head flash red
    if (state == ngames::snake::BoardState::lose) {
        head_attr |= A_BLINK | COLOR_PAIR(ngames::snake::COLOR_PAIR_COLLISION);
    }
    wattron(window, head_attr);
    mvwaddch(window, head_row, head_col, head_char);
    wattroff(window, head_attr);
}

/**
 * Draw the apple.
 * @param window Window.
 * @param apple Apple location (row, cell) on the board.
 */
void draw_apple(WINDOW* window, const std::optional<std::pair<int, int>>& apple)
{
    if (!apple.has_value()) {
        return;
    }
    const auto [row, col] = apple.value();
    const auto attr = A_BOLD | COLOR_PAIR(ngames::snake::COLOR_PAIR_APPLE);
    wattron(window, attr);
    mvwaddch(window, row, col, '*');
    wattroff(window, attr);
}

}  // namespace


namespace ngames::snake
{

Board::Board(int rows, int cols, int start_y, int start_x, WINDOW* border_window)
    : Component(subwin(border_window, rows, cols, start_y, start_x)),
      rows(rows),
      cols(cols)
{
    assert(rows >= MIN_ROWS);
    assert(cols >= MIN_COLS);

    reset();
}

void Board::refresh() const
{
    werase(window);
    draw_snake(window, snake, state);
    draw_apple(window, apple);
    wnoutrefresh(window);
}

void Board::tick()
{
    if (state != BoardState::active) {
        return;
    }
    // if collision, player has lost
    if (check_collision()) {
        state = BoardState::lose;
        return;
    }
    // otherwise, move the snake forwards
    const bool grow_snake = snake.next_head() == apple;
    snake.step(grow_snake);
    if (grow_snake) {
        ++score;
        apple = find_unoccupied();
    }
    // if no possible apple location, then player has won
    if (!apple.has_value()) {
        state = BoardState::win;
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

std::optional<std::pair<int, int>> Board::find_unoccupied() const
{
    // seed RNG with current time
    std::srand(clock());

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

    if (empty_idxs.empty()) {
        return std::nullopt;
    }

    // draw random index
    const int idx_idx = std::rand() % empty_idxs.size();
    const int idx = empty_idxs[idx_idx];
    const int row = idx / cols;
    const int col = idx % cols;

    return std::make_pair(row, col);
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

void Board::reset()
{
    // snake starts at center top
    const int snake_head_row = INIT_SNAKE_LENGTH - 1;
    const int snake_head_col = (cols - 1) / 2;
    snake = Snake(snake_head_row, snake_head_col, Direction::down, INIT_SNAKE_LENGTH);

    // check snake endpoints are inside board
    for (const auto& [row, col] : {snake.chain.front(), snake.chain.back()}) {
        assert(0 <= row && row < rows);
        assert(0 <= col && col < cols);
    }

    // initialize apple at random location
    apple = find_unoccupied();

    state = BoardState::active;
    score = 0;
}

}  // namespace ngames::snake
