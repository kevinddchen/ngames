#include <games/snakes/board.hpp>

#include <games/snakes/ui.hpp>


namespace games::snakes
{

Board::Board(int rows, int cols, int start_y, int start_x)
    : Component(newwin(rows + 2 * BORDER_WIDTH, cols + 2 * BORDER_WIDTH, start_y, start_x)),
      rows(rows),
      cols(cols),
      snake(1, 1, LEFT, 3, rows, cols)
{
}

void Board::refresh() const
{
    wclear(window);
    box(window, 0, 0);  // create window border
    snake.draw(window);
    wrefresh(window);
}

}  // namespace games::snakes
