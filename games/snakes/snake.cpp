#include <games/snakes/snake.hpp>


namespace games::snakes
{

Snake::Snake(int head_row, int head_col, Direction direction, int length) : direction(direction)
{
    assert(length > 0);

    const auto [drow, dcol] = dir2vec(direction);
    // populate chain in a straight line
    for (int i = 0; i < length; ++i) {
        chain.emplace_back(head_row - i * drow, head_col - i * dcol);
    }
}

void Snake::draw(WINDOW* window) const
{
    // head is drawn specially
    const auto [head_row, head_col] = chain.front();
    switch (direction) {
        case Direction::up:
            mvwaddch(window, head_row, head_col, '^');
            break;
        case Direction::down:
            mvwaddch(window, head_row, head_col, 'v');
            break;
        case Direction::left:
            mvwaddch(window, head_row, head_col, '<');
            break;
        case Direction::right:
            mvwaddch(window, head_row, head_col, '>');
            break;
    }

    for (auto it = chain.begin() + 1; it != chain.end(); ++it) {
        const auto [row, col] = *it;
        mvwaddch(window, row, col, '@');
    }
}

void Snake::step()
{
    const auto [head_row, head_col] = chain.front();
    const auto [drow, dcol] = dir2vec(direction);
    chain.emplace_front(head_row + drow, head_col + dcol);
    chain.pop_back();
}

}  // namespace games::snakes
