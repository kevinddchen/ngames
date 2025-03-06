#pragma once

#include "ui.h"


namespace mines
{

/**
 * Text displaying instructions.
 */
class TextInstructions : public Component
{
public:
    /**
     * Create text.
     * @param start_y y-coordinate of the top-left corner of the window.
     * @param start_x x-coordinate of the top-left corner of the window.
     */
    TextInstructions(int start_y, int start_x);

    /**
     * Refresh the text viewed by the user.
     */
    void refresh() const override;

    static constexpr int HEIGHT = 5;
    static constexpr int WIDTH = 32;
};

}  // namespace mines
