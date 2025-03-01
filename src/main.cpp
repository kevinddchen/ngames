#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

#include "app.h"
#include "common.h"
#include "ui.h"


/**
 * Print usage help text and then exit the program.
 */
[[noreturn]] static void help_and_exit()
{
    fprintf(stderr, "\n");
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "  ./mines b        beginner     (9x9, 10 mines)\n");
    fprintf(stderr, "  ./mines i        intermediate (16x16, 40 mines)\n");
    fprintf(stderr, "  ./mines e        expert       (30x16, 99 mines)\n");
    fprintf(stderr, "  ./mines r c m    custom       (r x c, m mines)\n");
    exit(EXIT_FAILURE);
}

/**
 * Convert string to integer. If an error occurs, print a helpful message to
 * the user and then exit the program.
 * @param str The string to convert.
 * @param min If provided, will also check that the integer is greater than or
 * equal to this.
 */
static int str_to_int(const std::string& str, std::optional<int> min = std::nullopt)
{
    int i;
    try {
        i = std::stoi(str);
    } catch (std::invalid_argument const&) {
        fprintf(stderr, "Input not a number: %s\n", str.c_str());
        help_and_exit();
    } catch (std::out_of_range const&) {
        fprintf(stderr, "Input too large: %s\n", str.c_str());
        help_and_exit();
    }

    if (min.has_value() && i < min.value()) {
        fprintf(stderr, "Input %d too small; must be at least %d\n", i, min.value());
        help_and_exit();
    }

    return i;
}

struct Args {
    int rows;
    int cols;
    int mines;
};

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
            const int rows = str_to_int(argv[1], 1);
            const int cols = str_to_int(argv[2], 1);
            const int mines = str_to_int(argv[3], 0);

            // since first cell is always empty, can have at most (rows * cols - 1) mines
            if (mines > rows * cols - 1) {
                fprintf(stderr, "Too many mines.\n");
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
