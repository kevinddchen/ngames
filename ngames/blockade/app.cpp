#include <ngames/blockade/app.hpp>

#include <ngames/blockade/ui.hpp>

#include <thread>


namespace
{

inline std::chrono::steady_clock::time_point now()
{
    return std::chrono::steady_clock::now();
}

}  // namespace


namespace ngames::blockade
{

App::App(int rows, int cols, double ticks_per_sec)
    : ticks_per_sec(ticks_per_sec),
      board_border(rows, cols, MARGIN_TOP, MARGIN_LEFT),
      board(rows, cols, board_border.inner_start_y(), board_border.inner_start_x(), board_border.window),
      text_end_game(board, board_border.bottom(), MARGIN_LEFT),
      text_instructions(text_end_game.bottom(), MARGIN_LEFT)
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
    board_border.refresh();
    board.refresh();
    text_end_game.refresh();
    text_instructions.refresh();
    doupdate();
}

void App::run()
{
    // How much time passes between frames
    constexpr std::chrono::duration<double, std::milli> frame_interval(1000.0 / FRAMES_PER_SEC);
    // How many frames pass between ticks
    const int tick_interval_frames = FRAMES_PER_SEC / ticks_per_sec;

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
                if (iframe % tick_interval_frames == 0) {
                    board.tick();
                }
                break;
        }

        refresh();

        // wait until frame ends
        const std::chrono::duration<double, std::milli> remaining_interval = frame_interval - (now() - t_frame);
        std::this_thread::sleep_for(max(remaining_interval, std::chrono::duration<double, std::milli>::zero()));
    }
}

App::Signal App::handle_keystroke(int key)
{
    // handle keystroke
    switch (key) {
        case 'a':
            board.set_snake_direction(Board::Player::one, snake::Direction::left);
            break;
        case 's':
            board.set_snake_direction(Board::Player::one, snake::Direction::down);
            break;
        case 'w':
            board.set_snake_direction(Board::Player::one, snake::Direction::up);
            break;
        case 'd':
            board.set_snake_direction(Board::Player::one, snake::Direction::right);
            break;
        case KEY_LEFT:
            board.set_snake_direction(Board::Player::two, snake::Direction::left);
            break;
        case KEY_DOWN:
            board.set_snake_direction(Board::Player::two, snake::Direction::down);
            break;
        case KEY_UP:
            board.set_snake_direction(Board::Player::two, snake::Direction::up);
            break;
        case KEY_RIGHT:
            board.set_snake_direction(Board::Player::two, snake::Direction::right);
            break;
        case 'z':  // new game
            board.reset();
            return Signal::reset;
        case 'r':  // refresh
            clearok(curscr, true);
            break;
        case 'q':  // quit
            return Signal::quit;
    }
    return Signal::none;
}

}  // namespace ngames::blockade
