#pragma once

#include <games/snakes/board.hpp>

#include <games/common/component.hpp>


namespace games::snakes
{

/**
 * Snakes application.
 */
class App : private Component
{
public:
    /**
     * Create application.
     * @param rows Number of rows for the Snakes board.
     * @param cols Number of columns for the Snakes board.
     */
    App(int rows, int cols);

    /**
     * Run the application.
     */
    void run();

private:
    /**
     * Refresh the app viewed by the user.
     */
    void refresh() const override;

    Board board;
};

}  // namespace games::snakes
