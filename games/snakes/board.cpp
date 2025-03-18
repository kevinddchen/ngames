#include <games/snakes/board.hpp>


namespace games::snakes
{

Board::Board(int rows, int cols, int start_y, int start_x, WINDOW* border_window)
    : Component(subwin(border_window, rows, cols, start_y, start_x)),
      rows(rows),
      cols(cols),
      snake(1, 4, Direction::right, 3)
{
    // Check snake endpoints are inside board
    for (const auto& [row, col] : {snake.head(), snake.tail()}) {
        assert(0 <= row && row < rows);
        assert(0 <= col && col < cols);
    }
}

void Board::refresh() const
{
    werase(window);
    snake.draw(window);
    wnoutrefresh(window);
}

void Board::tick()
{
    snake.step();
}

}  // namespace games::snakes
