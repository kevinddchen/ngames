#pragma once

#include <ngames/snake/direction.hpp>

#include <ncurses.h>

#include <deque>
#include <optional>


namespace ngames::snake
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

    Snake() {};

    /**
     * Returns the cell (row, col) in front of the snake.
     */
    std::pair<int, int> next_head() const;

    /**
     * Step the snake forward one cell. Does not check for any kind of collisions.
     * @param grow If true, does not delete the tail. Snake length increases by 1.
     */
    void step(bool grow);

    /**
     * Draw the snake on a window.
     * @param window Window.
     * @param head_attr Head attribute.
     * @param body_attr Body attribute.
     */
    void draw(WINDOW* window, attr_t head_attr = A_BOLD, attr_t body_attr = A_BOLD) const;

    // Direction of snake.
    Direction direction;
    // Direction of snake during previous step, if any.
    std::optional<Direction> prev_direction;

    // Chain of cells (row, col) that make up the snake body. Head is front of
    // chain, and tail is back of chain.
    std::deque<std::pair<int, int>> chain;
};

}  // namespace ngames::snake
