#include "TicTacToe.hpp"

const int MAX_VALUE = 9999;
const int MIN_VALUE = -9999;

TicTacToe::TicTacToe() : board(3, std::vector<char>(3, ' ')), currentPlayer('X'), gameEnded(false) {}

void TicTacToe::printBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << board[i][j];
            if (j < 2) std::cout << "|";
        }
        std::cout << std::endl;
        if (i < 2) std::cout << "-----" << std::endl;
    }
}

bool TicTacToe::checkWinForPlayer(char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return true;
        }
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true;
    }
    return false;
}

bool TicTacToe::checkWin() {
    return checkWinForPlayer('X') || checkWinForPlayer('O');
}

bool TicTacToe::checkDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') return false;
    return true;
}

int TicTacToe::minimax(bool isMaximizing) {
    if (checkWinForPlayer('X')) return -1;
    if (checkWinForPlayer('O')) return 1;
    if (checkDraw()) return 0;

    if (isMaximizing) {
        int maxEval = MIN_VALUE;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int evaluation = minimax(false);
                    maxEval = std::max(maxEval, evaluation);
                    board[i][j] = ' ';
                }
            }
        }
        return maxEval;
    } else {
        int minEval = MAX_VALUE;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int evaluation = minimax(true);
                    minEval = std::min(minEval, evaluation);
                    board[i][j] = ' ';
                }
            }
        }
        return minEval;
    }
}

std::pair<int, int> TicTacToe::findBestMove() {
    int bestValue = MIN_VALUE;
    std::pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int moveValue = minimax(false);
                board[i][j] = ' ';

                if (moveValue > bestValue) {
                    bestValue = moveValue;
                    bestMove = {i, j};
                }
            }
        }
    }
    return bestMove;
}

void TicTacToe::playGame() {
    while (!gameEnded) {
        printBoard();

        if (currentPlayer == 'X') {
            int x, y;
            do {
                std::cout << "Jogador X, insira a coordenada x (0, 1, 2): ";
                std::cin >> x;
                std::cout << "Insira a coordenada y (0, 1, 2): ";
                std::cin >> y;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    x = -1; // Invalid value to continue the loop
                }
            } while (x < 0 || x >= 3 || y < 0 || y >= 3 || board[y][x] != ' ');

            board[y][x] = 'X';
        } else {
            std::pair<int, int> move = findBestMove();
            board[move.first][move.second] = 'O';
        }

        gameEnded = checkWin() || checkDraw();
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    printBoard();

    if (checkWinForPlayer('X')) {
        std::cout << "Jogador X venceu!\n";
    } else if (checkWinForPlayer('O')) {
        std::cout << "Jogador O venceu!\n";
    } else {
        std::cout << "Empate!\n";
    }
}
