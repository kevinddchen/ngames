#include <games/snakes/snake.hpp>


namespace games::snakes
{

Snake::Snake(int head_y, int head_x, Direction direction, int length) : direction(direction)
{
    const auto [dy, dx] = dir2vec(direction);
    // populate chain in a straight line
    for (int i = 0; i < length; ++i) {
        chain.emplace_back(head_y - i * dy, head_x - i * dx);
    }
}

void Snake::draw(WINDOW* window) const
{
    // head is drawn specially
    const auto [head_y, head_x] = chain.front();
    switch (direction) {
        case Direction::up:
            mvwaddch(window, head_y, head_x, '^');
            break;
        case Direction::down:
            mvwaddch(window, head_y, head_x, 'v');
            break;
        case Direction::left:
            mvwaddch(window, head_y, head_x, '<');
            break;
        case Direction::right:
            mvwaddch(window, head_y, head_x, '>');
            break;
    }

    for (int i = 1; i < static_cast<int>(chain.size()); ++i) {
        const auto [y, x] = chain[i];
        mvwaddch(window, y, x, '*');
    }
}

void Snake::step()
{
    const auto [head_y, head_x] = chain.front();
    const auto [dy, dx] = dir2vec(direction);
    chain.emplace_front(head_y + dy, head_x + dx);
    chain.pop_back();
}

}  // namespace games::snakes
