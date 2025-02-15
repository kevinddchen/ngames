#include "board.h"
#include "common.h"

int main(int argc, char** argv)
{
    mines::Board board(10, 8, 10);
    board.print();

    return 0;
}
