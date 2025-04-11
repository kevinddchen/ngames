#include <ngames/mines/app.hpp>

#include <ngames/common/ncurses.hpp>

#include <stdexcept>
#include <string>

#include <cstring>


/**
 * Print usage help text and then exit the program.
 */
[[noreturn]] static void help_and_exit()
{
    fprintf(stderr, "usage:\n");
    fprintf(stderr, "  mines b                beginner     (9 x 9, 10 mines)\n");
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
    size_t pos;
    try {
        i = std::stoi(str, &pos);
    } catch (std::invalid_argument const&) {
        fprintf(stderr, "Not an integer: %s\n", str);
        help_and_exit();
    } catch (std::out_of_range const&) {
        fprintf(stderr, "Number too large: %s\n", str);
        help_and_exit();
    }
    if (pos != std::strlen(str)) {
        fprintf(stderr, "Not an integer: %s\n", str);
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

            const int min_rows = ngames::mines::Minesweeper::MIN_ROWS;
            const int min_cols = ngames::mines::Minesweeper::MIN_COLS;
            const int min_mines = ngames::mines::Minesweeper::MIN_MINES;

            if (rows < min_rows) {
                fprintf(stderr, "Not enough rows (%d); must be at least %d\n", rows, min_rows);
                help_and_exit();
            }
            if (cols < min_cols) {
                fprintf(stderr, "Not enough columns (%d); must be at least %d\n", cols, min_cols);
                help_and_exit();
            }
            if (mines < min_mines) {
                fprintf(stderr, "Not enough mines (%d); must be at least %d\n", mines, min_mines);
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

    ngames::init_ncurses();

    ngames::mines::App app(args.rows, args.cols, args.mines);
    app.run();

    ngames::end_ncurses();
    return EXIT_SUCCESS;
}
