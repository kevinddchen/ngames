#pragma once

#include <games/snakes/snake.hpp>

#include <games/common/component.hpp>


namespace games::snakes
{

constexpr std::pair<int, int> UP = {-1, 0};
constexpr std::pair<int, int> DOWN = {1, 0};
constexpr std::pair<int, int> LEFT = {0, -1};
constexpr std::pair<int, int> RIGHT = {0, 1};

/**
 * Board containing Snakes game.
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

    const int rows;
    const int cols;

private:
    Snake snake;
};

}  // namespace games::snakes
