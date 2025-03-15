#pragma once

#include <games/snakes/direction.hpp>

#include <ncurses.h>

#include <deque>


namespace games::snakes
{

/**
 * Snake state and controls.
 */
class Snake
{
public:
    /**
     * Create new snake.
     * @param head_y y-coordinate of the snake head in the board.
     * @param head_x x-coordinate of the snake head in the board.
     * @param direction Direction of snake.
     * @param length Length of snake, in number of characters.
     */
    Snake(int head_y, int head_x, Direction direction, int length);

    /**
     * Draw the snake on the given window.
     * @param window Window to draw on.
     */
    void draw(WINDOW* window) const;

    inline const std::pair<int, int>& head() const { return chain.front(); }

    inline const std::pair<int, int>& tail() const { return chain.back(); }

    /**
     * Step the snake forward one cell.
     */
    void step();

    inline void set_direction(Direction dir) { direction = dir; }

private:
    // Direction of snake.
    Direction direction;

    // Chain of cells (y, x) that make up the snake body
    std::deque<std::pair<int, int>> chain;
};

}  // namespace games::snakes
