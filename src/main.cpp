#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

#include "app.h"
#include "common.h"
#include "ui.h"


constexpr int MIN_ROWS = 1;
constexpr int MIN_COLS = 1;
constexpr int MIN_MINES = 0;

/**
 * Print usage help text and then exit the program.
 */
[[noreturn]] static void help_and_exit()
{
    fprintf(stderr, "usage:\n");
    fprintf(stderr, "  mines b                beginner     (9x9,   10 mines)\n");
    fprintf(stderr, "  mines i                intermediate (16x16, 40 mines)\n");
    fprintf(stderr, "  mines e                expert       (30x16, 99 mines)\n");
    fprintf(stderr, "  mines <r> <c> <m>      custom       (r x c,  m mines)\n");
    exit(EXIT_FAILURE);
}

/**
 * Convert string to integer. If an error occurs, prints a helpful message to
 * the user and then exits the program.
 * @param str The string to convert.
 */
static int str_to_int(const char* str)
{
    int i;
    try {
        i = std::atoi(str);
    } catch (std::invalid_argument const&) {
        fprintf(stderr, "Not a number: %s\n", str);
        help_and_exit();
    } catch (std::out_of_range const&) {
        fprintf(stderr, "Number too large: %s\n", str);
        help_and_exit();
    }
    return i;
}

struct Args {
    int rows;
    int cols;
    int mines;
};

/**
 * Parse command line arguments. If an error occurs, prints a helpful message
 * to the user and then exits the program.
 * @param argc
 * @param argv
 */
static Args get_args(int argc, char** argv)
{
    switch (argc) {
        case 1:
            help_and_exit();
        case 2: {
            const std::string difficulty = argv[1];
            if (difficulty == "b") {
                return {.rows = 9, .cols = 9, .mines = 10};
            }
            if (difficulty == "i") {
                return {.rows = 16, .cols = 16, .mines = 40};
            }
            if (difficulty == "e") {
                return {.rows = 16, .cols = 30, .mines = 99};
            }
            fprintf(stderr, "Unknown difficulty: %s\n", argv[1]);
            help_and_exit();
        }
        case 3:
            fprintf(stderr, "Invalid options: %s %s\n", argv[1], argv[2]);
            help_and_exit();
        case 4: {
            const int rows = str_to_int(argv[1]);
            const int cols = str_to_int(argv[2]);
            const int mines = str_to_int(argv[3]);

            if (rows < MIN_ROWS) {
                fprintf(stderr, "Not enough rows (%d); must be at least %d\n", rows, MIN_ROWS);
                help_and_exit();
            }
            if (cols < MIN_COLS) {
                fprintf(stderr, "Not enough columns (%d); must be at least %d\n", cols, MIN_COLS);
                help_and_exit();
            }
            if (mines < MIN_MINES) {
                fprintf(stderr, "Not enough mines (%d); must be at least %d\n", mines, MIN_MINES);
                help_and_exit();
            }
            // since first cell is always empty, can have at most (rows * cols - 1) mines
            const int max_mines = rows * cols - 1;
            if (mines > max_mines) {
                fprintf(stderr, "Too many mines (%d); can be at most %d\n", mines, max_mines);
                help_and_exit();
            }

            return {.rows = rows, .cols = cols, .mines = mines};
        }
        default:
            fprintf(stderr, "Too many options.\n");
            help_and_exit();
    }
}

int main(int argc, char** argv)
{
    const Args args = get_args(argc, argv);

    mines::init_ncurses();

    mines::App app(args.rows, args.cols, args.mines);
    app.run();

    return EXIT_SUCCESS;
}
