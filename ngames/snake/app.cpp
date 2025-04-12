#include <ngames/snake/app.hpp>

#include <ngames/snake/ui.hpp>

#include <thread>


namespace
{

inline std::chrono::steady_clock::time_point now()
{
    return std::chrono::steady_clock::now();
}

}  // namespace


namespace ngames::snake
{

App::App(int rows, int cols, int frames_per_tick, double frames_per_sec)
    : frames_per_tick(frames_per_tick),
      frames_per_sec(frames_per_sec),
      text_score(board, MARGIN_TOP, MARGIN_LEFT),
      board_border(rows, cols, text_score.bottom(), MARGIN_LEFT),
      board(rows, cols, board_border.inner_start_y(), board_border.inner_start_x(), board_border.window),
      text_instructions(board_border.bottom() + 1, MARGIN_LEFT)
{
    init_colors();
    curs_set(0);                  // hide cursor
    keypad(board.window, true);   // allow arrow keys
    nodelay(board.window, true);  // user input is non-blocking

    // initial print
    refresh();
}

void App::refresh() const
{
    text_score.refresh();
    board_border.refresh();
    board.refresh();
    text_instructions.refresh();
    doupdate();
}

void App::run()
{
    // How much time passes between frames
    const std::chrono::duration<double, std::milli> frame_interval(1000.0 / frames_per_sec);

    bool loop = true;
    for (long iframe = 1; loop; ++iframe) {
        const auto t_frame = now();

        // get user key
        const auto key = wgetch(board.window);
        const Signal signal = handle_keystroke(key);

        // handle special actions, if any
        switch (signal) {
            case Signal::reset:
                board.reset();
                // restart tick
                iframe = 0;
                break;
            case Signal::quit:
                // break the loop
                loop = false;
                break;
            case Signal::none:
                // proceed as normal
                if (iframe % frames_per_tick == 0) {
                    board.tick();
                }
                break;
            default:
                assert(false);
        }

        refresh();

        // clear input buffer to avoid keystrokes from building up
        flushinp();

        // wait until frame ends
        const std::chrono::duration<double, std::milli> remaining_interval = frame_interval - (now() - t_frame);
        std::this_thread::sleep_for(max(remaining_interval, std::chrono::duration<double, std::milli>::zero()));
    }
}

App::Signal App::handle_keystroke(int key)
{
    // handle keystroke
    switch (key) {
        case ERR:  // unset key
            break;
        case 'h':
        case KEY_LEFT:
            board.set_snake_direction(Direction::left);
            break;
        case 'j':
        case KEY_DOWN:
            board.set_snake_direction(Direction::down);
            break;
        case 'k':
        case KEY_UP:
            board.set_snake_direction(Direction::up);
            break;
        case 'l':
        case KEY_RIGHT:
            board.set_snake_direction(Direction::right);
            break;
        case 'z':  // new game
            board.reset();
            return Signal::reset;
        case 'r':  // refresh
            clearok(curscr, true);
            break;
        case 'q':  // quit
            return Signal::quit;
        default:
            assert(false);
    }
    return Signal::none;
}

}  // namespace ngames::snake
