#pragma once

#include <ngames/blockade/board.hpp>
#include <ngames/blockade/text_end_game.hpp>
#include <ngames/blockade/text_instructions.hpp>

#include <ngames/common/border.hpp>


namespace ngames::blockade
{

/**
 * Blockade application. Manages user input and game loop.
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
     * @param rows Number of rows for the Blockade board.
     * @param cols Number of columns for the Blockade board.
     * @param ticks_per_sec Tick rate.
     */
    App(int rows = 15, int cols = 21, double ticks_per_sec = 1.0);

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

    Border board_border;
    Board board;
    TextEndGame text_end_game;
    TextInstructions text_instructions;
};

}  // namespace ngames::blockade
