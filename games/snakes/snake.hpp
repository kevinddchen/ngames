#pragma once

#include <games/snakes/direction.hpp>

#include <deque>


namespace games::snakes
{

/**
 * Container for snake data, and some basic manipulations.
 */
struct Snake {
    /**
     * Create new snake.
     * @param head_row Cell row for the snake head.
     * @param head_col Cell column for the snake head.
     * @param direction Direction for the snake.
     * @param length Length of snake, in number of characters.
     */
    Snake(int head_row, int head_col, Direction direction, int length);

    /**
     * Returns the cell (row, col) in front of the snake.
     */
    std::pair<int, int> peek_forward() const;

    /**
     * Step the snake forward one cell.
     * @param grow If true, does not delete the tail and snake length increases
     * by 1.
     */
    void step(bool grow);

    // Direction of snake.
    Direction direction;

    // Chain of cells (row, col) that make up the snake body. Head is front of
    // deque, and tail is back of deque.
    std::deque<std::pair<int, int>> chain;
};

}  // namespace games::snakes
