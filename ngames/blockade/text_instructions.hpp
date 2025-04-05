#pragma once

#include <ngames/common/component.hpp>


namespace ngames::blockade
{

/**
 * Text displaying instructions.
 */
class TextInstructions : public Component
{
public:
    static constexpr int HEIGHT = 4;
    static constexpr int WIDTH = 80;

    /**
     * Create text.
     * @param start_y y-coordinate of the top-left corner of the window.
     * @param start_x x-coordinate of the top-left corner of the window.
     */
    TextInstructions(int start_y, int start_x);

    /**
     * Refresh the window text.
     */
    void refresh() const override;
};

}  // namespace ngames::blockade
