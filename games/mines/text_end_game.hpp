#pragma once

#include <games/mines/board.hpp>

#include <games/common/component.hpp>


namespace games::mines
{

/**
 * Text displaying end game message.
 */
class TextEndGame : public Component
{
public:
    static constexpr int HEIGHT = 1;
    static constexpr int WIDTH = 80;

    /**
     * Create text.
     * @param board Reference to board object.
     * @param start_y y-coordinate of the top-left corner of the window.
     * @param start_x x-coordinate of the top-left corner of the window.
     */
    TextEndGame(const Board& board, int start_y, int start_x);

    /**
     * Refresh the window text.
     */
    void refresh() const override;

private:
    const Board& board;
};

}  // namespace games::mines
