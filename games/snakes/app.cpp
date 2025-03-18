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
    curs_set(0);                  // Hide cursor
    keypad(board.window, true);   // Allow arrow keys
    nodelay(board.window, true);  // User input is non-blocking

    refresh();  // Initial print
}

void App::run()
{
    // How many ms pass between frames
    constexpr std::chrono::duration<double, std::milli> frame_interval_ms(1000.0 / FRAMES_PER_SEC);
    // How many frames pass between updates
    constexpr long update_interval_frames = FRAMES_PER_SEC / UPDATES_PER_SEC;

    const auto t_start = std::chrono::steady_clock::now();
    for (long iframe = 1;; ++iframe) {
        const auto t_curr = std::chrono::steady_clock::now();

        // Wait until appropriate time
        const auto target_diff_ms = iframe * frame_interval_ms;
        const std::chrono::duration<double, std::milli> curr_diff_ms = t_curr - t_start;
        std::this_thread::sleep_for(target_diff_ms - curr_diff_ms);

        // Get user key
        const auto key = wgetch(board.window);
        if (!handle_keystroke(key)) {
            break;
        }

        // Update board
        if (iframe % update_interval_frames == 0) {
            board.update();
            board.refresh();
            doupdate();
        }

        // flushinp();  // clear input buffer to avoid keystrokes from building up
    }
}

void App::refresh() const
{
    board_border.refresh();
    board.refresh();
    doupdate();
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
