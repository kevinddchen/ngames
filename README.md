# ngames

Games in your terminal.
The following games have been implemented:
- `mines`: Minesweeper
- `snake`: Snake
- `blockade`: Blockade (a 2-player version of Snake)

## Installation

You need [ncurses](https://invisible-island.net/ncurses/) in order to build.
It usually comes by default on Linux and macOS, but you can check if you have it by running `tic -V` in your terminal.

To build, run

```
make all
```

or build a specific game,

```
make <name>
```

## Run

After building, run a game,

```
./bin/<name>
```

The games typically use Vim `hjkl` controls or arrow keys to move.
The `q` key will quit the game.
The `z` key will reset the game.
The `r` key will refresh the display, e.g. if something caused the game to render incorrectly.
