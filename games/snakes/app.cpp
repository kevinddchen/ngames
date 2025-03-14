#include <games/snakes/app.hpp>

#include <games/snakes/ui.hpp>


namespace games::snakes
{

App::App(int rows, int cols) : Component(stdscr), board(rows, cols, MARGIN_TOP, MARGIN_LEFT)
{
    refresh();  // Initial print
}

void App::run()
{
    wgetch(board.window);
}

void App::refresh() const
{
    board.refresh();
}

}  // namespace games::snakes
