#pragma once

#include <ngames/snake/direction.hpp>
#include <ngames/snake/snake.hpp>

#include <ngames/common/component.hpp>

#include <optional>


namespace ngames::snake
{

/**
 * Front-end for the Snake game. Manages game state and window viewed by the
 * player.
 */
class Board : public Component
{
public:
    static constexpr int MIN_ROWS = 5;
    static constexpr int MIN_COLS = 5;

    static constexpr int INIT_SNAKE_LENGTH = 3;

    enum State { active, win, lose };

    /**
     * Create new Snake game.
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
     * @param dir Desired direction.
     *
     * @returns Return code. A non-zero value means that an error occurred and
     * the game state was not been changed. The possible error codes are
     *   1: game is inactive.
     *   2: new direction will point towards the snake's second cell.
     */
    int set_snake_direction(Direction dir);

    /**
     * Returns game state.
     */
    inline State get_state() const { return state; }

    inline int get_score() const { return score; }

    const int rows;
    const int cols;

private:
    /**
     * Finds a random cell on the board that is not occupied by the snake. Used
     * for finding new locations for the apple after it has been eaten.
     * @returns (row, col) of unoccupied cell, or null if all cells are occupied.
     */
    std::optional<std::pair<int, int>> find_unoccupied() const;

    /**
     * Returns `true` if the snake's future position will collide into itself
     * or a wall.
     */
    bool check_collision() const;

    // Snake instance.
    std::optional<Snake> snake;
    // Apple location (row, cell) on the board.
    std::optional<std::pair<int, int>> apple;

    // Whether the game is active.
    State state;
    // Player score.
    int score;
};

}  // namespace ngames::snake
