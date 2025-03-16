#pragma once

#include <games/snakes/snake.hpp>

#include <games/common/component.hpp>


namespace games::snakes
{

/**
 * Board managing the Snakes game.
 */
class Board : public Component
{
public:
    /**
     * Create new Snakes game.
     * @param rows Number of rows.
     * @param cols Number of columns.
     * @param start_y y-coordinate of the top-left corner of the window.
     * @param start_x x-coordinate of the top-left corner of the window.
     */
    Board(int rows, int cols, int start_y, int start_x);

    /**
     * Refresh the board viewed by the user.
     */
    void refresh() const override;

    /**
     * Update the state of the board.
     */
    void update();

    inline void set_snake_direction(Direction dir) { snake.set_direction(dir); }

    const int rows;
    const int cols;

private:
    Snake snake;
};

}  // namespace games::snakes
