#pragma once

#include <ngames/blockade/board.hpp>
#include <ngames/blockade/text_end_game.hpp>
#include <ngames/blockade/text_instructions.hpp>

#include <ngames/common/border.hpp>

#include <array>


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
     * @param frames_per_tick A tick is an update of the game, and happens every `frames_per_tick`th frame.
     * @param frames_per_sec Number of frames to render per second.
     */
    App(int rows = 15, int cols = 21, int frames_per_tick = 20, double frames_per_sec = 30.0);

    /**
     * Run the application.
     */
    void run();

private:
    static constexpr int UNSET_KEY = -1;

    /**
     * Indicate special actions for the game loop.
     */
    enum Signal { none, reset, quit };

    /**
     * Refresh the windows of the application.
     */
    void refresh() const;

    /**
     * Get keystrokes for the frame.
     * @returns Array of keystrokes: { player one, player two, control (e.g. reset) }. -1 means no keystroke.
     */
    std::array<int, 3> get_keystrokes() const;

    /**
     * Perform actions associated with given keystrokes for each player.
     * @param keys Keys pressed.
     * @returns A `Signal` that may require special actions for the game loop.
     */
    Signal handle_keystrokes(const std::array<int, 3>& keys);

    int frames_per_tick;
    double frames_per_sec;

    Border board_border;
    Board board;
    TextEndGame text_end_game;
    TextInstructions text_instructions;
};

}  // namespace ngames::blockade
