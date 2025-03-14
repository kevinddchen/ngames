#pragma once

#include <ncurses.h>

#include <deque>


namespace games::snakes
{

constexpr std::pair<int, int> UP = {-1, 0};
constexpr std::pair<int, int> DOWN = {1, 0};
constexpr std::pair<int, int> LEFT = {0, -1};
constexpr std::pair<int, int> RIGHT = {0, 1};

/**
 * Snake state and controls.
 */
class Snake
{
public:
    /**
     * Create new snake.
     */
    Snake(int head_y, int head_x, std::pair<int, int> direction, int length, int rows, int cols);

    /**
     * Draw the snake on the given window.
     */
    void draw(WINDOW* window) const;

private:
    int head_y;
    int head_x;
    std::pair<int, int> direction;

    // Chain of cells (y, x) that make up the snake body
    std::deque<std::pair<int, int>> chain;
};

}  // namespace games::snakes
