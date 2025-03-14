#include <games/snakes/board.hpp>


namespace games::snakes
{

Board::Board(int rows, int cols, int start_y, int start_x)
    : Component(newwin(rows, cols, start_y, start_x)),
      rows(rows),
      cols(cols),
      snake(1, 1, LEFT, 3, rows, cols)
{
}

void Board::refresh() const
{
    wclear(window);
    snake.draw(window);
    wrefresh(window);
}

}  // namespace games::snakes
