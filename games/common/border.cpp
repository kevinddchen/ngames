#include <games/common/border.hpp>


namespace games
{

Border::Border(int rows, int cols, int start_y, int start_x)
    : Component(newwin(rows + 2 * BORDER_WIDTH, cols + 2 * BORDER_WIDTH, start_y, start_x))
{
}

void Border::refresh() const
{
    // no `werase` since we don't want to erase the subwindow.
    box(window, 0, 0);
    wnoutrefresh(window);
}

}  // namespace games
