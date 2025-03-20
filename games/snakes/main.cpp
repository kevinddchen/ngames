#include <games/snakes/app.hpp>

#include <games/common/ncurses.hpp>


int main()
{
    games::init_ncurses();

    games::snakes::App app(10, 10);
    app.run();

    games::end_ncurses();
    return EXIT_SUCCESS;
}
