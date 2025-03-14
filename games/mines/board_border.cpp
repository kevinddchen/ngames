#include <games/mines/board_border.hpp>


namespace games::mines
{

BoardBorder::BoardBorder(int rows, int cols, int start_y, int start_x)
    : Component(newwin(rows + 2 * BORDER_WIDTH, cols + 2 * BORDER_WIDTH, start_y, start_x))
{
}

void BoardBorder::refresh() const
{
    wclear(window);
    box(window, 0, 0);  // create window border
    wrefresh(window);
}

}  // namespace games::mines
