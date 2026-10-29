#include <iostream>
#include <iomanip>
#include "sudoku.h"

using namespace std;

// Print game board to screen
ostream &operator<<(ostream &os, Sudoku &s)
{
    s.Print_Board(os);
    return os;
}

// Class Constructor - Setting up the board
Sudoku::Sudoku()
{
    for (int r = 0; r < 9; r++)
    {
        for (int c = 0; c < 9; c++)
        {
            board[r][c] = 0;
            isOriginal[r][c] = false;
        }
    }
}

// Clear the board when game is finished
void Sudoku::Clear()
{
    for (int r = 0; r < 9; r++)
    {
        for (int c = 0; c < 9; c++)
        {
            board[r][c] = 0;
        }
    }
}

void Sudoku::Print_Board(ostream &os)
{
    // Print column label and numbers across top of the board
    os << "          C       O       L\n"
       << endl;
    os << "        1 2 3   4 5 6   7 8 9\n"
       << endl;
    os << "       +-------+-------+-------+" << endl;

    char rowLabels[9] = {' ', 'R', ' ', ' ', 'O', ' ', ' ', 'W', ' '};
    for (int r = 0; r < 9; r++)
    {
        // Print row label and numbers down the side of the board
        os << rowLabels[r] << "  " << (r + 1) << "   | ";

        for (int c = 0; c < 9; c++)
        {
            // Put a '.' in empty boxes or the value in filled boxes
            if (board[r][c] == 0)
                os << ". ";
            else if (isOriginal[r][c])
            {
                // Pre-filled box - normal color
                os << board[r][c] << " ";
            }
            else
            {
                // User Input values - cyan
                os << "\033[36m" << board[r][c] << "\033[0m" << " ";
            }

            if ((c + 1) % 3 == 0)
                os << "| ";
        }
        os << endl;

        if ((r + 1) % 3 == 0)
        {
            os << "       +-------+-------+-------+" << endl;
        }
    }
}

void Sudoku::Generate_Game(char diff)
{
    // Base valid solution grid
    int baseGrid[9][9] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}};

    // Set baseGrid as board
    for (int r = 0; r < 9; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            board[r][c] = baseGrid[r][c];
            isOriginal[r][c] = true;
        }
    }

    // Seed random number
    srand(time(0));

    // Scramble Rows
    int rowGroup = rand() % 3;
    int r1 = (rowGroup * 3) + (rand() % 3);
    int r2 = (rowGroup * 3) + (rand() % 3);
    for (int c = 0; c < 9; ++c)
    {
        int temp = board[r1][c];
        board[r1][c] = board[r2][c];
        board[r2][c] = temp;
    }

    // Scramble Columns
    int colGroup = rand() % 3;
    int c1 = (colGroup * 3) + (rand() % 3);
    int c2 = (colGroup * 3) + (rand() % 3);
    for (int r = 0; r < 9; ++r)
    {
        int temp = board[r][c1];
        board[r][c1] = board[r][c2];
        board[r][c2] = temp;
    }

    // Swap digits (ex: every 5 will become a 2)
    int mapping[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 1; i <= 9; ++i)
    {
        int swapIdx = (rand() % 9) + 1;
        int temp = mapping[i];
        mapping[i] = mapping[swapIdx];
        mapping[swapIdx] = temp;
    }

    // Remap digits across entire board
    for (int r = 0; r < 9; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            board[r][c] = mapping[board[r][c]];
        }
    }

    // Determine how many cells to remove based on difficulty
    int cellsToRemove;

    if (diff == 'E')
        cellsToRemove = 40;
    else if (diff == 'M')
        cellsToRemove = 48;
    else if (diff == 'H')
        cellsToRemove = 54;

    srand(time(0));
    int removed = 0;
    while (removed < cellsToRemove)
    {
        int r = rand() % 9;
        int c = rand() % 9;
        if (board[r][c] != 0)
        {
            board[r][c] = 0;
            removed++;
        }
    }

    // Mark original pre-filled boxes so the player cannot overwrite them
    for (int r = 0; r < 9; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            if (board[r][c] != 0)
            {
                isOriginal[r][c] = true;
            }
            else
            {
                isOriginal[r][c] = false;
            }
        }
    }
}

bool Sudoku::Set_Cell(int row, int col, int val)
{
    if (isOriginal[row][col])
    {
        // Prevents user from overwriting pre-set values
        cout << "\nCannot modify original pre-filled cell!" << endl;
        return false;
    }

    // Sets sell to user value
    board[row][col] = val;
    return true;
}

bool Sudoku::Check_Board()
{
    // Check the rows, columns, and grids are valid solutions
    for (int i = 0; i < 9; i++)
    {
        if (!Check_Row(i))
            return false;
        if (!Check_Col(i))
            return false;
        if (!Check_Grid(i))
            return false;
    }
    return true;
}

bool Sudoku::Check_Row(const int row)
{
    int value[9];

    // Collect all values in that row
    for (int i = 1; i <= 9; i++)
    {
        value[i] = board[row][i];
    }

    // Check for duplicates in the row
    for (int i = 1; i <= 9; i++)
    {
        for (int j = i + 1; j <= 9; j++)
        {
            if (value[i] == value[j])
                return false;
        }
    }
    // No duplicates, row is valid.
    return true;
}

bool Sudoku::Check_Col(const int col)
{
    int value[9];

    // Collect all values in that col
    for (int r = 1; r <= 9; r++)
    {
        value[r] = board[r][col];
    }

    // Check for duplicates in the col
    for (int i = 1; i <= 9; i++)
    {
        for (int j = i + 1; j <= 9; j++)
        {
            if (value[i] == value[j])
                return false;
        }
    }
    // No duplicates, col is valid.
    return true;
}

bool Sudoku::Check_Grid(const int grid)
{
    int value[9];
    int startRow, startCol, index = 0;

    // Find the starting row
    if (grid == 0 || grid == 1 || grid == 2)
        startRow = 0;
    else if (grid == 3 || grid == 4 || grid == 5)
        startRow = 3;
    else
        startRow = 6;

    // Find the starting column
    if (grid == 0 || grid == 3 || grid == 6)
        startCol = 0;
    else if (grid == 1 || grid == 4 || grid == 7)
        startCol = 3;
    else
        startCol = 6;

    // Get values for that grid
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            value[index] = board[startRow + r][startCol + c];
            index++;
        }
    }

    // Check for duplicates
    for (int i = 0; i < 9; i++)
    {
        for (int j = i + 1; j < 9; j++)
        {
            if (value[i] == value[j])
                return false;
        }
    }
    return true;
}
