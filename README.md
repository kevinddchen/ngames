# mines

Minesweeper in your terminal.

## Installation

You need [ncurses](https://invisible-island.net/ncurses/) in order to build.
It usually comes by default on Linux and macOS, but you can check if you have it by running `tic -V` in your terminal.

To build, run

```
make all
```

## Run

After building, run

```
./bin/mines
```

The cursor can be moved using vim controls (i.e. `hjkl`) or arrow keys.
`f` places a flag, and `space` opens a cell.
You can [chord](https://en.wikipedia.org/wiki/Chording#Minesweeper_tactic) by clicking on an already opened cell.
