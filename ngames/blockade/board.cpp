#include <ngames/blockade/board.hpp>

#include <ngames/blockade/ui.hpp>


namespace ngames::blockade
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

void Board::reset()
{
    // snake_one starts at top left
    snake_one = snake::Snake(1, 1, snake::Direction::down, 1);

    // snake_two starts at bottom right
    snake_two = snake::Snake(rows - 2, cols - 2, snake::Direction::up, 1);

    state = State::active;
    collide_one = false;
    collide_two = false;
}

void Board::refresh() const
{
    werase(window);
    // if snake collided, make snake head flash red
    constexpr auto default_head_attr = A_BOLD;
    constexpr auto collide_head_attr = default_head_attr | A_BLINK | COLOR_PAIR(COLOR_PAIR_COLLISION);
    snake_one->draw(window, collide_one ? collide_head_attr : default_head_attr);
    snake_two->draw(window, collide_two ? collide_head_attr : default_head_attr);
    wnoutrefresh(window);
}

void Board::tick()
{
    if (state != State::active) {
        return;
    }
    // check for collisions
    if (check_collision(*snake_one)) {
        collide_one = true;
    }
    if (check_collision(*snake_two)) {
        collide_two = true;
    }
    // check for endgame
    if (collide_one && collide_two) {
        state = State::tie;
        return;
    } else if (collide_one) {
        state = State::win_two;
        return;
    } else if (collide_two) {
        state = State::win_one;
        return;
    }
    // otherwise, move the snakes forwards
    snake_one->step(true);
    snake_two->step(true);
}

int Board::set_snake_direction(Player player, snake::Direction dir)
{
    switch (player) {
        case Player::one:
            return set_snake_direction(*snake_one, dir);
        case Player::two:
            return set_snake_direction(*snake_two, dir);
    }
}

int Board::set_snake_direction(snake::Snake& snake, snake::Direction dir)
{
    if (state != State::active) {
        return 1;
    } else if (snake.chain.size() > 1 && snake.next_head(&dir) == snake.chain[1]) {
        return 2;
    }
    snake.direction = dir;
    return 0;
}

bool Board::check_collision(const snake::Snake& snake) const
{
    const auto next = snake.next_head();
    // check collision with wall
    if (next.first < 0 || next.first >= rows || next.second < 0 || next.second >= cols) {
        return true;
    }
    // check collision with both snakes.
    // we exclude the snake tail since it will move away in time.
    for (const auto& other_snake : {snake_one, snake_two}) {
        for (auto it = other_snake->chain.begin(); it != other_snake->chain.end() - 1; ++it) {
            if (next == *it) {
                return true;
            }
        }
    }
    return false;
}

}  // namespace ngames::blockade
