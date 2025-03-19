#pragma once

#include <games/snakes/direction.hpp>
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

    inline void set_snake_direction(Direction dir) { snake.direction = dir; }

    const int rows;
    const int cols;

private:
    Snake snake;
};

}  // namespace games::snakes
