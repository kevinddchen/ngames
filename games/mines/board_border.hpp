#pragma once

#include <games/common/component.hpp>


namespace games::mines
{

/**
 * Border for the Minesweeper board.
 */
class BoardBorder : public Component
{
public:
    // Window border width, in number of chars
    static constexpr int BORDER_WIDTH = 1;

    /**
     * Create border.
     * @param rows Number of rows inside the border.
     * @param cols Number of columns inside the border.
     * @param start_y y-coordinate of the top-left corner of the window.
     * @param start_x x-coordinate of the top-left corner of the window.
     */
    BoardBorder(int rows, int cols, int start_y, int start_x);

    /**
     * Refresh the border viewed by the user.
     */
    void refresh() const override;

    /**
     * y-coordinate of the top-left corner inside the border.
     */
    inline int inner_start_y() const { return top() + BORDER_WIDTH; }

    /**
     * x-coordinate of the top-left corner inside the border.
     */
    inline int inner_start_x() const { return left() + BORDER_WIDTH; }
};

}  // namespace games::mines
