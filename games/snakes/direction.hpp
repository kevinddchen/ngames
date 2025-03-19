#pragma once

#include <utility>


namespace games::snakes
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
    }
}

}  // namespace games::snakes
