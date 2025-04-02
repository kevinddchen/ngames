#include <ngames/blockade/board.hpp>

#include <ngames/blockade/ui.hpp>


namespace
{

/**
 * Return the opponent player.
 * @param player Player.
 */
ngames::blockade::Board::Player get_opponent(ngames::blockade::Board::Player player)
{
    switch (player) {
        case ngames::blockade::Board::Player::one:
            return ngames::blockade::Board::Player::two;
        case ngames::blockade::Board::Player::two:
            return ngames::blockade::Board::Player::one;
    }
}

}  // namespace


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
    if (check_collision(Player::one)) {
        collide_one = true;
    }
    if (check_collision(Player::two)) {
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
    snake::Snake& snake = get_snake(player);
    if (state != State::active) {
        return 1;
    } else if (snake.chain.size() > 1 && snake.next_head(&dir) == snake.chain[1]) {
        return 2;
    }
    snake.direction = dir;
    return 0;
}

bool Board::check_collision(Player player) const
{
    const snake::Snake& snake = get_snake(player);
    const auto next_head = snake.next_head();
    // check collision with wall
    if (next_head.first < 0 || next_head.first >= rows || next_head.second < 0 || next_head.second >= cols) {
        return true;
    }
    // check collision with both snakes.
    for (const auto& other_player : {Player::one, Player::two}) {
        const snake::Snake& other_snake = get_snake(other_player);
        for (auto it = other_snake.chain.begin(); it != other_snake.chain.end(); ++it) {
            if (next_head == *it) {
                return true;
            }
        }
    }
    // check collision with other snake next head.
    const Player opponent = get_opponent(player);
    const snake::Snake& opponent_snake = get_snake(opponent);
    if (next_head == opponent_snake.next_head()) {
        return true;
    }
    return false;
}

const snake::Snake& Board::get_snake(Player player) const
{
    switch (player) {
        case Player::one:
            return *snake_one;
        case Player::two:
            return *snake_two;
    }
}

snake::Snake& Board::get_snake(Player player)
{
    return const_cast<snake::Snake&>(const_cast<const Board*>(this)->get_snake(player));
}


}  // namespace ngames::blockade
