#pragma once

#include <ngames/common/component.hpp>
#include <ngames/snake/direction.hpp>
#include <ngames/snake/snake.hpp>

#include <optional>


namespace ngames::blockade
{

enum Player { one, two };

/**
 * Front-end for the Blockade game. Manages game state and window viewed by the
 * players.
 */
class Board : public Component
{
public:
    static constexpr int MIN_ROWS = 5;
    static constexpr int MIN_COLS = 5;

    /**
     * Create new Blockade game.
     * @param rows Number of rows.
     * @param cols Number of columns.
     * @param start_y y-coordinate of the top-left corner of the window.
     * @param start_x x-coordinate of the top-left corner of the window.
     * @param border_window Parent window containing border.
     */
    Board(int rows, int cols, int start_y, int start_x, WINDOW* border_window);

    /**
     * Refresh the window displaying the board.
     */
    void refresh() const override;

    /**
     * Update the state of the board by stepping the snake forward one cell.
     */
    void tick();

    /**
     * Attempt to set the snake direction.
     *
     * @param player Player.
     * @param dir Desired direction.
     *
     * @returns Return code. A non-zero value means that an error occurred and
     * the game state was not been changed. The possible error codes are
     *   1: game is inactive.
     *   2: new direction will point towards the snake's second cell.
     */
    int set_snake_direction(Player player, snake::Direction dir);

    /**
     * Reset the game.
     */
    void reset();

    const int rows;
    const int cols;

private:
    // Player 1 snake instance.
    snake::Snake snake_1;
    // Player 2 snake instance.
    snake::Snake snake_2;
};

}  // namespace ngames::blockade
