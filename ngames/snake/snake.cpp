#include <ngames/snake/snake.hpp>

#include <cassert>


namespace ngames::snake
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

std::pair<int, int> Snake::next_head(std::optional<Direction> dir) const
{
    const auto [head_row, head_col] = chain.front();
    const auto [drow, dcol] = dir2vec(dir.value_or(direction));
    return {head_row + drow, head_col + dcol};
}

void Snake::step(bool grow)
{
    chain.push_front(next_head());
    if (!grow) {
        chain.pop_back();
    }
}

void Snake::draw(WINDOW* window, attr_t head_attr, attr_t body_attr) const
{
    // draw snake body excluding head
    wattron(window, body_attr);
    for (auto it = chain.begin() + 1; it != chain.end(); ++it) {
        const auto [row, col] = *it;
        mvwaddch(window, row, col, '@');
    }
    wattroff(window, body_attr);

    // head is drawn specially
    char head_char;
    switch (direction) {
        case ngames::snake::Direction::up:
            head_char = '^';
            break;
        case ngames::snake::Direction::down:
            head_char = 'v';
            break;
        case ngames::snake::Direction::left:
            head_char = '<';
            break;
        case ngames::snake::Direction::right:
            head_char = '>';
            break;
    }
    const auto [head_row, head_col] = chain.front();

    wattron(window, head_attr);
    mvwaddch(window, head_row, head_col, head_char);
    wattroff(window, head_attr);
}

}  // namespace ngames::snake
