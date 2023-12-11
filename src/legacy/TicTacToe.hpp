#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include <vector>
#include <iostream>

class TicTacToe {
private:
    std::vector<std::vector<char>> board;
    char currentPlayer;
    bool gameEnded;

    bool checkWin();
    bool checkDraw();
public:
    TicTacToe();
    void playGame();
    void printBoard();
};

#endif  // TICTACTOE_HPP
