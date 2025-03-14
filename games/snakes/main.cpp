#include <games/snakes/app.hpp>

#include <games/common/ncurses.hpp>


int main()
{
    games::init_ncurses();

    games::snakes::App app(20, 20);
    app.run();

    games::end_ncurses();
    return 0;
    // return EXIT_SUCCESS;
}
