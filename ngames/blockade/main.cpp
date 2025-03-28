#include <ngames/blockade/app.hpp>

#include <ngames/common/ncurses.hpp>

#include <cstdlib>


int main()
{
    ngames::init_ncurses();

    ngames::blockade::App app(15, 21, 1.0);
    app.run();

    ngames::end_ncurses();
    return EXIT_SUCCESS;
}
