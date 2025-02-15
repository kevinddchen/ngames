#include "board.h"
#include "common.h"
#include "ui.h"

int main(int argc, char** argv)
{
    mines::Board board(10, 8, 10);
    mines::UserInterface ui(board);

    ui.run();

    return 0;
}
