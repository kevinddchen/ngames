#pragma once

#include <ncurses.h>

#include "board.h"


namespace mines
{

/**
 * Text displaying the number of mines remaining.
 */
class TextMineCount
{
public:
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
    void refresh() const;

    WINDOW* const window;

private:
    const Board& board;
};

}  // namespace mines
