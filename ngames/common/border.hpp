#pragma once

#include <ngames/common/component.hpp>


namespace ngames
{

/**
 * Window border.
 */
class Border : public Component
{
public:
    // Window border width, in number of chars
    static constexpr int BORDER_WIDTH = 1;

    /**
     * Create border.
     * @param rows Number of rows inside the border.
     * @param cols Number of columns inside the border.
     * @param start_y y-coordinate of the top-left corner of the window border.
     * @param start_x x-coordinate of the top-left corner of the window border.
     */
    Border(int rows, int cols, int start_y, int start_x);

    /**
     * Refresh the window displaying the border.
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

}  // namespace ngames
