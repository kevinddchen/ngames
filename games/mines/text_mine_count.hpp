#pragma once

#include <games/mines/board.hpp>

#include <games/common/component.hpp>


namespace games::mines
{

/**
 * Text displaying the number of mines remaining.
 */
class TextMineCount : public Component
{
public:
    static constexpr int HEIGHT = 1;
    static constexpr int WIDTH = 32;

    /**
     * Create text.
     * @param board Reference to board object.
     * @param start_y y-coordinate of the top-left corner of the window.
     * @param start_x x-coordinate of the top-left corner of the window.
     */
    TextMineCount(const Board& board, int start_y, int start_x);

    /**
     * Refresh the text viewed by the user.
     */
    void refresh() const override;

private:
    const Board& board;
};

}  // namespace games::mines
