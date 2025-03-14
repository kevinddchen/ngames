#include <games/snakes/app.hpp>

#include <chrono>
#include <thread>


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
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        board.update();
        refresh();
    }
}

void App::refresh() const
{
    board_border.refresh();
    board.refresh();
}

}  // namespace games::snakes
