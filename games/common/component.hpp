#pragma once

#include <ncurses.h>


namespace games
{

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

}  // namespace games
