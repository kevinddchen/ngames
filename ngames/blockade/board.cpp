#include <ngames/blockade/board.hpp>


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

void Board::refresh() const
{
    werase(window);
    snake_1.draw(window);
    snake_2.draw(window);
    wnoutrefresh(window);
}

void Board::tick()
{
    snake_1.step(true);
    snake_2.step(true);
}

int Board::set_snake_direction(Player player, snake::Direction dir)
{
    snake::Snake* snake;
    switch (player) {
        case Player::one:
            snake = &snake_1;
            break;
        case Player::two:
            snake = &snake_2;
            break;
    }
    if (snake->chain.size() > 1 && snake->next_head(dir) == snake->chain[1]) {
        return 2;
    }
    snake->direction = dir;
    return 0;
}

void Board::reset()
{
    // snake_1 starts at top left
    snake_1 = snake::Snake(1, 1, snake::Direction::down, 1);

    // snake_2 starts at bottom right
    snake_2 = snake::Snake(rows - 2, cols - 2, snake::Direction::up, 1);
}

}  // namespace ngames::blockade
