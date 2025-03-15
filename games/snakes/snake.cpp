#include <games/snakes/snake.hpp>


namespace games::snakes
{

Snake::Snake(std::pair<int, int> head, std::pair<int, int> direction, int length) : direction(direction)
{
    // populate chain in a straight line
    for (int i = 0; i < length; ++i) {
        chain.emplace_back(head.first - i * direction.first, head.second - i * direction.second);
    }
}

void Snake::draw(WINDOW* window) const
{
    // head is drawn specially
    const auto [head_y, head_x] = chain.front();
    if (direction == LEFT) {
        mvwaddch(window, head_y, head_x, '<');
    } else if (direction == DOWN) {
        mvwaddch(window, head_y, head_x, 'v');
    } else if (direction == UP) {
        mvwaddch(window, head_y, head_x, '^');
    } else if (direction == RIGHT) {
        mvwaddch(window, head_y, head_x, '>');
    }

    for (int i = 1; i < static_cast<int>(chain.size()); ++i) {
        const auto [y, x] = chain[i];
        mvwaddch(window, y, x, '@');
    }
}

void Snake::step()
{
    const auto& head = chain.front();
    chain.emplace_front(head.first + direction.first, head.second + direction.second);
    chain.pop_back();
}

}  // namespace games::snakes
