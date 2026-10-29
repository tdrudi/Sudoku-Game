#ifndef GAME_H
#define GAME_H
#include "sudoku.h"

using namespace std;

class Game
{
private:
    void Clear();
    char getDifficulty();

public:
    Game();
    void RunGame();
    bool MakeMove(int row, int col, int val, Sudoku &gameBoard, bool &isMatch);
};

#endif