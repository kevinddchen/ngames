#include <games/snakes/snake.hpp>


namespace games::snakes
{

Snake::Snake(int head_y, int head_x, std::pair<int, int> direction, int length, int rows, int cols)
    : head_y(head_y),
      head_x(head_x),
      direction(direction)
{
    // check head coordinates
    assert(0 <= head_y && head_y < rows);
    assert(0 <= head_x && head_x < cols);

    // populate chain
    for (int i = 0; i < length; ++i) {
        chain.emplace_back(head_y - i * direction.first, head_x - i * direction.second);
    }

    // check tail coordinates
    const auto [tail_y, tail_x] = chain.back();
    assert(0 <= tail_y && tail_y < rows);
    assert(0 <= tail_x && tail_x < cols);
}

void Snake::draw(WINDOW* window) const
{
    for (const auto& [y, x] : chain) {
        mvwaddch(window, y, x, '@');
    }
    // TODO: remove
    (void)head_y;
    (void)head_x;
}

}  // namespace games::snakes
