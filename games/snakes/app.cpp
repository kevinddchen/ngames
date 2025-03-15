#include <games/snakes/app.hpp>

#include <thread>


namespace
{

/**
 * Loop that periodically updates and refreshes the board.
 * @param board Pointer to board.
 */
void loop_update_refresh(games::snakes::Board* const board)
{
    assert(board != nullptr);
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        board->update();
        board->refresh();
    }
}

}  // namespace


namespace games::snakes
{

App::App(int rows, int cols)
    : Component(stdscr),
      board_border(rows, cols, MARGIN_TOP, MARGIN_LEFT),
      board(rows, cols, board_border.inner_start_y(), board_border.inner_start_x())
{
    curs_set(0);                 // Hide cursor
    keypad(board.window, true);  // Allow arrow keys

    refresh();  // Initial print
}

void App::run()
{
    // daemon thread continuously updates and refreshes the board every second
    std::thread loop_thread(loop_update_refresh, &board);
    loop_thread.detach();

    while (true) {
        const int key = wgetch(board.window);
        if (!handle_keystroke(key)) {
            break;
        }
    }
}

void App::refresh() const
{
    board_border.refresh();
    board.refresh();
}

bool App::handle_keystroke(int key)
{
    // handle keystroke
    switch (key) {
        case 'h':
        case KEY_LEFT:
            board.set_snake_direction(Direction::left);
            board.refresh();
            break;
        case 'j':
        case KEY_DOWN:
            board.set_snake_direction(Direction::down);
            board.refresh();
            break;
        case 'k':
        case KEY_UP:
            board.set_snake_direction(Direction::up);
            board.refresh();
            break;
        case 'l':
        case KEY_RIGHT:
            board.set_snake_direction(Direction::right);
            board.refresh();
            break;
        case 'r':  // refresh
            refresh();
            break;
        case 'q':  // quit
            return false;
    }
    return true;
}

}  // namespace games::snakes
