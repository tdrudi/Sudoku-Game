#include <iostream>
#include <iomanip>
#include "game.h"

using namespace std;

Game::Game()
{
    RunGame();
}

// Clear screen to reprint game board
void Game::Clear()
{
    cout << "\033[2J\033[H";
}

char Game::getDifficulty()
{
    char difficulty;
    while (true)
    {
        cout << "\n--Select Game Difficulty--" << endl;
        cout << "      [E] Easy" << endl;
        cout << "      [M] Medium" << endl;
        cout << "      [H] Hard" << endl;
        cout << "      [Q] Quit" << endl;
        cout << "Enter choice (E/M/H/Q): ";
        cin >> difficulty;
        cout << endl;

        if (toupper(difficulty) == 'E' || toupper(difficulty) == 'M' || toupper(difficulty) == 'H')
        {
            return toupper(difficulty);
        }
        else if (toupper(difficulty) == 'Q')
        {
            cout << "Thanks for playing!";
            return difficulty;
        }
        else
        {

            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void Game::RunGame()
{
    char playAgain = 'Y';

    while (toupper(playAgain) == 'Y')
    {
        char difficulty = getDifficulty();

        if (difficulty == 'Q')
            break;

        Sudoku gameboard;
        gameboard.Generate_Game(difficulty);

        int row, col, val;
        bool isMatch = true;

        while (isMatch)
        {
            cout << gameboard << endl;
            cout << "\n--- Enter Your Move ---" << endl;
            cout << "Enter Row [1-9] (or 0 to quit): ";
            cin >> row;

            if (row == 0)
            {
                // Pass 0 to trigger your quit/dashboard condition
                MakeMove(0, 0, 0, gameboard, isMatch);
            }
            else
            {
                cout << "Enter Column [1-9]: ";
                cin >> col;

                cout << "Enter Value [1-9]: ";
                cin >> val;

                // Send the user input to make the move
                MakeMove(row, col, val, gameboard, isMatch);
            }
            Clear();
        }
    }
    cout << "\nWould you like to play another game? (Y/N): ";
    cin >> playAgain;
}
bool Game::MakeMove(int row, int col, int val, Sudoku &gameBoard, bool &isMatch)
{
    // Check for quit condition
    if (row == 0 && col == 0 && val == 0)
    {
        isMatch = false;
        return true;
    }

    // Check boundary (input 1-9 only)
    if (row < 1 || row > 9 || col < 1 || col > 9 || val < 1 || val > 9)
    {
        char num;
        cout << "\nInvalid value. Try again: ";
        cin >> num;
        return false;
    }

    // Attempt to place the move (protects pre-filled clues)
    if (!gameBoard.Set_Cell(row - 1, col - 1, val))
    {
        char num;
        cout << "Enter any character to continue: ";
        cin >> num;
        return false;
    }

    // Check if puzzle is solved/valid
    if (gameBoard.Check_Board())
    {
        cout << "\nCONGRATULATIONS! You solved the puzzle successfully!\n";
        cout << gameBoard << endl;
        isMatch = false;
    }

    return true;
}
