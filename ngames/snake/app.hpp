#pragma once

#include <ngames/snake/board.hpp>
#include <ngames/snake/text_instructions.hpp>
#include <ngames/snake/text_score.hpp>

#include <ngames/common/border.hpp>


namespace ngames::snake
{

/**
 * Snake application. Manages user input and game loop.
 */
class App
{
public:
    // Frame rate
    static constexpr double FRAMES_PER_SEC = 30.0;

    // Top margin, in number of chars
    static constexpr int MARGIN_TOP = 1;
    // Left margin, in number of chars
    static constexpr int MARGIN_LEFT = 1;

    /**
     * Create application.
     * @param rows Number of rows for the Snake board.
     * @param cols Number of columns for the Snake board.
     * @param ticks_per_sec Tick rate.
     */
    App(int rows = 15, int cols = 21, double ticks_per_sec = 5.0);

    /**
     * Run the application.
     */
    void run();

private:
    /**
     * Indicate special actions for the game loop.
     */
    enum Signal { none, reset, quit };

    /**
     * Refresh the windows of the application.
     */
    void refresh() const;

    /**
     * Perform action associated with given keystroke.
     * @param key Key pressed.
     * @returns A `Signal` that may require special actions for the game loop.
     */
    Signal handle_keystroke(int key);

    double ticks_per_sec;

    TextScore text_score;
    Border board_border;
    Board board;
    TextInstructions text_instructions;
};

}  // namespace ngames::snake
