#include <games/snakes/app.hpp>


namespace games::snakes
{

App::App(int rows, int cols)
    : Component(stdscr),
      board_border(rows, cols, MARGIN_TOP, MARGIN_LEFT),
      board(rows, cols, board_border.inner_start_y(), board_border.inner_start_x())
{
    refresh();  // Initial print
}

void App::run()
{
    wgetch(board.window);
}

void App::refresh() const
{
    board_border.refresh();
    board.refresh();
}

}  // namespace games::snakes
