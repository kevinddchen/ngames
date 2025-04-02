#pragma once

#include <ngames/common/component.hpp>
#include <ngames/snake/direction.hpp>
#include <ngames/snake/snake.hpp>


namespace ngames::blockade
{

/**
 * Front-end for the Blockade game. Manages game state and window viewed by the
 * players.
 */
class Board : public Component
{
public:
    static constexpr int MIN_ROWS = 5;
    static constexpr int MIN_COLS = 5;

    enum Player { one, two };

    enum State { active, win_one, win_two, tie };

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
     * Reset the game.
     */
    void reset();

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
     * Returns game state.
     */
    inline State get_state() const { return state; }

    const int rows;
    const int cols;

private:
    /**
     * Private version of `set_snake_direction` that takes in the `Snake` struct to be edited.
     * @param snake Snake.
     * @param dir Desired direction.
     */
    int set_snake_direction(snake::Snake& snake, snake::Direction dir);

    /**
     * Returns `true` if the snake's future position will collide into itself
     * or a wall.
     * @param snake Snake.
     */
    bool check_collision(const snake::Snake& snake) const;

    // Player 1 snake instance.
    snake::Snake snake_one;
    // Player 2 snake instance.
    snake::Snake snake_two;

    // Whether the game is active.
    State state;
    // If player one has collided.
    bool collide_one;
    // If player two has collided.
    bool collide_two;
};

}  // namespace ngames::blockade
