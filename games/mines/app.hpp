#pragma once

#include <games/mines/board.hpp>
#include <games/mines/text_end_game.hpp>
#include <games/mines/text_instructions.hpp>
#include <games/mines/text_mine_count.hpp>

#include <games/common/border.hpp>
#include <games/common/component.hpp>


namespace games::mines
{

/**
 * Minesweeper application.
 */
class App : private Component
{
public:
    // Top margin, in number of chars
    static constexpr int MARGIN_TOP = 1;
    // Left margin, in number of chars
    static constexpr int MARGIN_LEFT = 1;

    /**
     * Create application.
     * @param rows Number of rows for the Minesweeper board.
     * @param cols Number of columns for the Minesweeper board.
     * @param mines Number of mines for the Minesweeper board.
     */
    App(int rows, int cols, int mines);

    /**
     * Run the application.
     */
    void run();

private:
    /**
     * Refresh the app viewed by the user.
     */
    void refresh() const override;

    /**
     * Perform action associated with given keystroke or mouse event.
     * @param key Key pressed.
     * @returns False when we want to quit.
     */
    bool handle_keystroke(int key);

    // y-coordinate of cursor, relative to board window.
    int cursor_y;
    // x-coordinate of cursor, relative to board window.
    int cursor_x;

    TextMineCount text_mine_count;
    Border board_border;
    Board board;
    TextEndGame text_end_game;
    TextInstructions text_instructions;
};

}  // namespace games::mines
