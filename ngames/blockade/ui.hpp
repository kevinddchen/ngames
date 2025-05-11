#pragma once

#include <ngames/common/ncurses.hpp>


namespace ngames::blockade
{

// Color pair for player one
constexpr short COLOR_PAIR_PLAYER_ONE = 1;
// Color pair for player two
constexpr short COLOR_PAIR_PLAYER_TWO = 2;
// Color pair for snake head when it collides
constexpr short COLOR_PAIR_COLLISION = 3;
// Color pair for instructions
constexpr short COLOR_PAIR_INSTRUCTIONS = 4;

/**
 * Initialize custom colors for Blockade.
 */
inline void init_colors()
{
    // define color pairs
    init_pair(COLOR_PAIR_PLAYER_ONE, COLOR_GREEN, COLOR_BLACK);
    init_pair(COLOR_PAIR_PLAYER_TWO, COLOR_RED, COLOR_BLACK);
    init_pair(COLOR_PAIR_COLLISION, COLOR_WHITE, COLOR_RED);
    init_pair(COLOR_PAIR_INSTRUCTIONS, COLOR_GREY, COLOR_BLACK);
};

}  // namespace ngames::blockade
