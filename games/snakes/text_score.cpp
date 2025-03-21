#include <games/snakes/text_score.hpp>


namespace games::snakes
{

TextScore::TextScore(const Board& board, int start_y, int start_x)
    : Component(newwin(TextScore::HEIGHT, TextScore::WIDTH, start_y, start_x)),
      board(board)
{
}

void TextScore::refresh() const
{
    werase(window);
    mvwprintw(window, 0, 0, "SCORE: %-4d", board.get_score());
    wnoutrefresh(window);
}

}  // namespace games::snakes
