#ifndef SUDOKU_H
#define SUDOKU_H
#include <iomanip>
#include <iostream>

using namespace std;

class Sudoku
{
private:
    int board[9][9];
    bool isOriginal[9][9];

public:
    Sudoku();
    void Clear();
    void Generate_Game(char difficulty);
    bool Set_Cell(int row, int col, int val);

    void Print_Board(ostream &os);
    bool Check_Board();
    bool Check_Row(const int row);
    bool Check_Col(const int col);
    bool Check_Grid(const int grid);
};

// Non Class Function
ostream &operator<<(ostream &os, Sudoku &s);

#endif