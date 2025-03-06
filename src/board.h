#pragma once

#include <optional>
#include <vector>

#include "game.h"
#include "ui.h"


namespace mines
{

enum BoardState { active, win, lose };

/**
 * Front-end for the Minesweeper game. Contains information about the game
 * known by the player, e.g. neighboring mine counts and flags, and maintains
 * the window viewed by the player.
 */
class Board : public Component
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
     * Click on a cell.
     *
     * If the cell is unopened, the cell will be opened. If the cell contains a
     * mine, the game will end. If the cell has no neighboring mines, all
     * neighboring unopened cells will also be opened (this happens
     * recursively).
     *
     * If the cell has already been opened and the number of neighboring flags
     * equals the number of neighboring mines, all neighboring unopened cells
     * will be opened (this happens recursively). This is called "chording".
     *
     * @param row Cell row.
     * @param col Cell column.
     *
     * @returns Return code. A non-zero value means that an error occurred and
     * the game state was not been changed. The possible error codes are
     *   1: game is inactive.
     *   2: cell has already been opened, and cannot be chorded.
     *   3: cell has been flagged.
     */
    int click_cell(int row, int col);

    /**
     * Toggle the flag for a cell.
     *
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
    inline bool is_active() const { return state == BoardState::active; }

    /**
     * Return number of flags used.
     */
    inline int get_num_flags() const { return num_flags; }

    /**
     * Returns true if player has won the game.
     */
    inline bool is_win() const { return state == BoardState::win; }

    /**
     * Refresh the board viewed by the user.
     */
    void refresh() const override;

    const int rows;
    const int cols;
    const int mines;

private:
    /**
     * Returns true if the cell can be opened.
     */
    inline bool can_open(int row, int col) const
    {
        return is_active() && !is_opened(row, col) && !is_flagged(row, col);
    }

    /**
     * Returns true if the cell can be chorded.
     */
    inline bool can_chord(int row, int col) const
    {
        return is_active() && is_opened(row, col) &&
               get_neighbor_mine_count(row, col) == count_neighbor_flags(row, col);
    }

    /**
     * Open an unopened cell. If the cell contains a mine, the game will end.
     * If the cell has no neighboring mines, all neighboring unopened cells
     * will also be opened (this happens recursively).
     * @param row Cell row.
     * @param col Cell column.
     */
    void open(int row, int col);

    /**
     * Open all neighboring unopened cells. See `open()` for more details.
     * @param row Cell row.
     * @param col Cell column.
     */
    void open_neighbors(int row, int col);

    inline bool is_known_mine(int row, int col) const { return is_known_mine_array[row][col]; }

    inline bool is_opened(int row, int col) const { return is_opened_array[row][col]; }

    inline bool is_flagged(int row, int col) const { return is_flagged_array[row][col]; }

    inline int get_neighbor_mine_count(int row, int col) const { return neighbor_mine_counts[row][col]; }

    int count_neighbor_flags(int row, int col) const;

    /**
     * Query `game` for locations of all mines.
     */
    void populate_known_mine_array();

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
    BoardState state;
    // Number of opened cells.
    int num_opened;
    // Number of flags used.
    int num_flags;
    // (row, column) of last opened cell.
    std::optional<std::pair<int, int>> last_opened;

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
