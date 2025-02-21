#pragma once

#include <vector>

#include <ncurses.h>

#include "game.h"


namespace mines
{

/**
 * Front-end for the Minesweeper game. Contains information about the game
 * known by the player, e.g. neighboring mine counts and flags.
 */
class Board
{
public:
    /**
     * Create new Minesweeper game.
     * @param rows Number of rows.
     * @param cols Number of columns.
     * @param mines Number of mines.
     * @param start_y y-coordinate of the top-left corner of the window.
     * @param start_x x-coordinate of the top-left corner of the window.
     */
    Board(int rows, int cols, int mines, int start_y, int start_x);

    /**
     * Returns true if cell is known to contain a mine.
     * @param row Cell row.
     * @param col Cell column.
     */
    inline bool is_known_mine(int row, int col) const { return is_known_mine_array[row][col]; }

    /**
     * Returns true if cell has been opened.
     * @param row Cell row.
     * @param col Cell column.
     */
    inline bool is_opened(int row, int col) const { return is_opened_array[row][col]; }

    /**
     * Open a cell. If the cell contains a mine, the game will end. If the cell
     * has no neighboring mines, all neighboring mines will also be opened
     * (this happens recursively).
     * @param row Cell row.
     * @param col Cell column.
     *
     * @returns Return code. A non-zero value means that an error occurred and
     * the game state was not been changed. The possible error codes are
     *   1: game is inactive.
     *   2: cell has already been opened.
     *   3: cell has been flagged.
     */
    int open(int row, int col);

    /**
     * Returns true if cell has been flagged.
     * @param row Cell row.
     * @param col Cell column.
     */
    inline bool is_flagged(int row, int col) const { return is_flagged_array[row][col]; }

    /**
     * Toggle the flag for a cell.
     * @param row Cell row.
     * @param col Cell column.
     *
     * @returns Return code. A non-zero value means that an error occurred and
     * the game state was not been changed. The possible error codes are
     *   1: game is inactive.
     *   2: cell has already been opened.
     */
    int toggle_flag(int row, int col);

    /**
     * Returns true if game is active.
     */
    inline bool is_active() const { return active; }

    /**
     * Return number of flags used.
     */
    inline int get_num_flags() const { return num_flags; }

    /**
     * Count the number of mines neighboring a cell. Returns -1 if the cell
     * has not been opened or contains a mine.
     * @param row Cell row.
     * @param col Cell column.
     */
    inline int get_neighbor_mine_count(int row, int col) const { return neighbor_mine_counts[row][col]; }

    /**
     * Refresh the board viewed by the user.
     */
    void refresh() const;

    const int rows;
    const int cols;
    const int mines;

    WINDOW* const window;

private:
    /**
     * Print the cell at the current cursor location, and then advance the
     * cursor.
     * @param row Cell row.
     * @param col Cell column.
     */
    void print_cell(int row, int col) const;

    // Game back-end.
    Game game;

    // Whether the game is active.
    bool active;
    // Number of opened cells.
    int num_opened;
    // Number of flags used.
    int num_flags;

    // Array with shape (rows, cols) tracking which cells are known to contain a mine.
    std::vector<std::vector<bool>> is_known_mine_array;
    // Array with shape (rows, cols) tracking which cells have been opened.
    std::vector<std::vector<bool>> is_opened_array;
    // Array with shape (rows, cols) tracking which cells have been flagged.
    std::vector<std::vector<bool>> is_flagged_array;
    // Array with shape (rows, cols) tracking neighbor mine counts for opened cells.
    std::vector<std::vector<int>> neighbor_mine_counts;
};

}  // namespace mines
