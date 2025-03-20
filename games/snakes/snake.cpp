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

}  // namespace games::snakes
