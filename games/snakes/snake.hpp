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
     * @param head (y, x) position of the snake head.
     * @param direction (dy, dx) unit vector pointing in direction of travel.
     * @param length Length of snake, in characters.
     */
    Snake(std::pair<int, int> head, std::pair<int, int> direction, int length);

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

    inline void set_direction(const std::pair<int, int>& dir) { direction = dir; }

private:
    // Unit vector (dy, dx) pointing in direction of travel.
    std::pair<int, int> direction;

    // Chain of cells (y, x) that make up the snake body
    std::deque<std::pair<int, int>> chain;
};

}  // namespace games::snakes
