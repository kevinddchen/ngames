#include <games/snakes/board.hpp>

#include <games/snakes/ui.hpp>


namespace
{

void draw_snake(WINDOW* window, const games::snakes::Snake& snake)
{
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

    for (auto it = snake.chain.begin() + 1; it != snake.chain.end(); ++it) {
        const auto [row, col] = *it;
        mvwaddch(window, row, col, '@');
    }
}

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
      snake(1, 1, Direction::left, 3),       // snake starts along top of board
      apple((rows - 1) / 2, (cols - 1) / 2)  // apple starts in the middle
{
    assert(rows >= MIN_ROWS);
    assert(cols >= MIN_COLS);

    // Check snake endpoints are inside board
    for (const auto& [row, col] : {snake.chain.front(), snake.chain.back()}) {
        assert(0 <= row && row < rows);
        assert(0 <= col && col < cols);
    }

    snake.direction = Direction::down;  // start snake pointing down
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
    const bool grow = snake.peek_forward() == apple;
    snake.step(grow);
}

}  // namespace games::snakes
