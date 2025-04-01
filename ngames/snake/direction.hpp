#pragma once

#include <utility>

#include <cassert>


namespace ngames::snake
{

enum Direction { up, down, left, right };

inline std::pair<int, int> dir2vec(Direction dir)
{
    switch (dir) {
        case Direction::up:
            return {-1, 0};
        case Direction::down:
            return {1, 0};
        case Direction::left:
            return {0, -1};
        case Direction::right:
            return {0, 1};
        default:
            assert(false);
    }
}

inline Direction opposite_direction(Direction dir)
{
    switch (dir) {
        case Direction::up:
            return Direction::down;
        case Direction::down:
            return Direction::up;
        case Direction::left:
            return Direction::right;
        case Direction::right:
            return Direction::left;
        default:
            assert(false);
    }
}

}  // namespace ngames::snake
