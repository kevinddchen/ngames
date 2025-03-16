#pragma once

#include <games/snakes/direction.hpp>

#include <ncurses.h>

#include <deque>


namespace games::snakes
{

/**
 * Class controlling the snake.
 */
class Snake
{
public:
    /**
     * Create new snake.
     * @param head_row Cell row for the snake head.
     * @param head_col Cell column for the snake head.
     * @param direction Direction for the snake.
     * @param length Length of snake, in number of characters.
     */
    Snake(int head_row, int head_col, Direction direction, int length);

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

    // Chain of cells (row, col) that make up the snake body. Front is head
    // and back is tail.
    std::deque<std::pair<int, int>> chain;
};

}  // namespace games::snakes
