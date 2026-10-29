### Sudoku

A command line Sudoku game built in C++.

This project is an expansion of a previous class assignment where the core objective was reading in puzzle files and validating whether they represented valid Sudoku boards. I expanded upon the foundational file-reading and validation logic to build a fully playable and interactive Sudoku game.

## Features and How to Play

- **Difficulty Selection:** Choose a difficulty level upon starting, which controls how many starting numbers are pre-filled on the board.
- **Board Generation:** Automatically generates a board based on your chosen difficulty.
- **Interactive Controls:** Input your moves turn-by-turn by entering the row, column, and value.
- **Validation:** Built-in verification ensuring that entered numbers conform to standard Sudoku rules (rows, columns, and 3 x 3 grids) once the board is fully filled.
- **Replayability:** Prompted to play again or exit upon finishing a game.

## Getting Started

Prerequisites:

- A C++ compiler supporting C++11 or higher (example: `g++`)
- `make` utility

Compiling and Running

1. Clone the repository:

```
git clone https://github.com/tdrudi/Sudoku-Game.git
cd sudoku-game
```

2. Build the project using MakeFile:

```
make
```

3. Run the game:

```
./main
```
