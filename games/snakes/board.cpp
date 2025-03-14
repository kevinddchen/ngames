#include <games/snakes/board.hpp>


namespace games::snakes
{

Board::Board(int rows, int cols, int start_y, int start_x)
    : Component(newwin(rows, cols, start_y, start_x)),
      rows(rows),
      cols(cols),
      snake({1, 4}, RIGHT, 3)
{
    // Check snake endpoints are inside board
    for (const auto& [y, x] : {snake.head(), snake.tail()}) {
        assert(0 <= y && y < rows);
        assert(0 <= x && x < cols);
    }
}

void Board::refresh() const
{
    wclear(window);
    snake.draw(window);
    wrefresh(window);
}

void Board::update()
{
    snake.step();
}

}  // namespace games::snakes
