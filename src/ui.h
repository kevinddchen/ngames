#pragma once

#include <ncurses.h>


namespace mines
{

// Window border width, in number of chars
constexpr int BORDER_WIDTH = 1;
// Top margin, in number of chars
constexpr int MARGIN_TOP = 1;
// Left margin, in number of chars
constexpr int MARGIN_LEFT = 1;

// New grey color
constexpr short COLOR_GREY = 8;

// Color pair for errors
constexpr short COLOR_PAIR_ERROR = 9;  // white text on red background
// Color pair for unopened cell
constexpr short COLOR_PAIR_UNOPENED = 8;  // grey text
// Color pair for winning text
constexpr short COLOR_PAIR_WIN = 2;  // green text
// Color pair for losing text
constexpr short COLOR_PAIR_LOSS = 3;  // red text
// Color pair for instructions
constexpr short COLOR_PAIR_INSTRUCTIONS = 8;  // grey text

/**
 * Initialize ncurses.
 */
void init_ncurses();

/**
 * Abstract base class for an interactive component.
 */
class Component
{
public:
    /**
     * Create component.
     * @param window Window displaying text for the component.
     */
    Component(WINDOW* window);

    virtual ~Component();

    /**
     * Return y-coordinate of top of component.
     */
    inline int top() const { return getbegy(window); }

    /**
     * Return y-coordinate of bottom of component.
     */
    inline int bottom() const { return getbegy(window) + getmaxy(window); }

    /**
     * Return x-coordinate of left of component.
     */
    inline int left() const { return getbegx(window); }

    /**
     * Return x-coordinate of right of component.
     */
    inline int right() const { return getbegx(window) + getmaxx(window); }

    /**
     * Refresh the text viewed by the user.
     */
    virtual void refresh() const = 0;

    WINDOW* const window;
};

}  // namespace mines
