#include <ngames/snake/app.hpp>

#include <ngames/snake/ui.hpp>

#include <thread>


namespace ngames::snake
{

App::App(int rows, int cols)
    : text_score(board, MARGIN_TOP, MARGIN_LEFT),
      board_border(rows, cols, text_score.bottom(), MARGIN_LEFT),
      board(rows, cols, board_border.inner_start_y(), board_border.inner_start_x(), board_border.window)
{
    init_colors();
    curs_set(0);                  // hide cursor
    keypad(board.window, true);   // allow arrow keys
    nodelay(board.window, true);  // user input is non-blocking

    // initial print
    refresh();
}

void App::run()
{
    // How many ms pass between frames
    constexpr std::chrono::duration<double, std::milli> frame_interval_ms(1000.0 / FRAMES_PER_SEC);
    // How many frames pass between ticks
    constexpr long tick_interval_frames = FRAMES_PER_SEC / TICKS_PER_SEC;

    const auto t_start = std::chrono::steady_clock::now();
    for (long iframe = 1;; ++iframe) {
        // wait until correct frame time
        const auto target_diff_ms = iframe * frame_interval_ms;
        const auto t_curr = std::chrono::steady_clock::now();
        const std::chrono::duration<double, std::milli> curr_diff_ms = t_curr - t_start;
        std::this_thread::sleep_for(target_diff_ms - curr_diff_ms);

        // get user key
        const auto key = wgetch(board.window);
        if (!handle_keystroke(key)) {
            break;
        }

        if (iframe % tick_interval_frames == 0) {
            board.tick();
        }

        refresh();

        // clear input buffer to avoid keystrokes from building up
        flushinp();
    }
}

void App::refresh() const
{
    text_score.refresh();
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
            if (board.set_snake_direction(Direction::left) == 0) {
                board.refresh();
            }
            break;
        case 'j':
        case KEY_DOWN:
            if (board.set_snake_direction(Direction::down) == 0) {
                board.refresh();
            }
            break;
        case 'k':
        case KEY_UP:
            if (board.set_snake_direction(Direction::up) == 0) {
                board.refresh();
            }
            break;
        case 'l':
        case KEY_RIGHT:
            if (board.set_snake_direction(Direction::right) == 0) {
                board.refresh();
            }
            break;
        case 'r':  // refresh
            refresh();
            break;
        case 'q':  // quit
            return false;
    }
    return true;
}

}  // namespace ngames::snake
