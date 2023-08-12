#include <iostream>
#include <vector>

using namespace std;

const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

struct Move {
    int row, col;
};

class TicTacToe {
private:
    char board[3][3];

public:
    TicTacToe() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                board[i][j] = EMPTY;
            }
        }
    }

    bool isMoveValid(int row, int col) {
        return (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == EMPTY);
    }

    bool isGameOver() {
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] != EMPTY && board[i][0] == board[i][1] && board[i][0] == board[i][2])
                return true;

            if (board[0][i] != EMPTY && board[0][i] == board[1][i] && board[0][i] == board[2][i])
                return true;
        }

        if (board[0][0] != EMPTY && board[0][0] == board[1][1] && board[0][0] == board[2][2])
            return true;

        if (board[0][2] != EMPTY && board[0][2] == board[1][1] && board[0][2] == board[2][0])
            return true;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == EMPTY)
                    return false;
            }
        }

        return true;
    }

    int evaluate() {
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
                if (board[i][0] == PLAYER_X)
                    return 10;
                else if (board[i][0] == PLAYER_O)
                    return -10;
            }

            if (board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
                if (board[0][i] == PLAYER_X)
                    return 10;
                else if (board[0][i] == PLAYER_O)
                    return -10;
            }
        }

        if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
            if (board[0][0] == PLAYER_X)
                return 10;
            else if (board[0][0] == PLAYER_O)
                return -10;
        }

        if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
            if (board[0][2] == PLAYER_X)
                return 10;
            else if (board[0][2] == PLAYER_O)
                return -10;
        }

        return 0;
    }

    int minimax(int depth, bool isMaximizing) {
        int score = evaluate();

        if (score == 10)
            return score;

        if (score == -10)
            return score;

        if (!isGameOver())
            return 0;

        if (isMaximizing) {
            int best = -1000;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (board[i][j] == EMPTY) {
                        board[i][j] = PLAYER_X;
                        best = max(best, minimax(depth + 1, !isMaximizing));
                        board[i][j] = EMPTY;
                    }
                }
            }
            return best;
        } else {
            int best = 1000;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (board[i][j] == EMPTY) {
                        board[i][j] = PLAYER_O;
                        best = min(best, minimax(depth + 1, !isMaximizing));
                        board[i][j] = EMPTY;
                    }
                }
            }
            return best;
        }
    }

    Move findBestMove() {
        int bestVal = -1000;
        Move bestMove;
        bestMove.row = -1;
        bestMove.col = -1;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_X;
                    int moveVal = minimax(0, false);
                    board[i][j] = EMPTY;

                    if (moveVal > bestVal) {
                        bestMove.row = i;
                        bestMove.col = j;
                        bestVal = moveVal;
                    }
                }
            }
        }

        return bestMove;
    }

    void printBoard() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }

    void play() {
        while (!isGameOver()) {
            printBoard();

            Move move;
            if (isGameOver()) {
                cout << "Game Over" << endl;
                break;
            }

            cout << "Enter row (0-2) for player O: ";
            cin >> move.row;
            cout << "Enter column (0-2) for player O: ";
            cin >> move.col;

            if (isMoveValid(move.row, move.col)) {
                board[move.row][move.col] = PLAYER_O;
            } else {
                cout << "Invalid move. Try again." << endl;
                continue;
            }

            if (isGameOver()) {
                cout << "Player O wins!" << endl;
                break;
            }

            Move bestMove = findBestMove();
            board[bestMove.row][bestMove.col] = PLAYER_X;

            if (isGameOver()) {
                cout << "Player X wins!" << endl;
                break;
            }
        }

        printBoard();
    }
};

int main() {
    TicTacToe game;
    game.play();

    return 0;
}
