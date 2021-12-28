#include<bits/stdc++.h>
#include "field.h"

using namespace std;

struct Move {
    int x, y;
};

bool is_move_left(Ui::Field board[3][3]) {
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 3; i++) {
            if (board[i][j] == Ui::Field::None) {
                return true;
            }
        }
    }
    return false;
}

int eval(Ui::Field board[3][3], Ui::Field player, Ui::Field opponent) {
    for (int y = 0; y < 3; y++) {
        if (board[y][0] == board[y][1] && board[y][1] == board[y][2]) {
            if (board[y][0] == player) {
                return 10;
            } else if (board[y][0] == opponent) {
                return -10;
            }
        }
    }

    for (int x = 0; x < 3; x++) {
        if (board[0][x] == board[1][x] && board[1][x] == board[2][x]) {
            if (board[0][x] == player) {
                return 10;
            } else if (board[0][x] == opponent) {
                return -10;
            }
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == player) {
            return 10;
        }
        else if (board[0][0] == opponent) {
            return -10;
        }
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == player) {
            return 10;
        } else if (board[0][2] == opponent) {
            return -10;
        }
    }

    return 0;
}

int minmax(Ui::Field board[3][3], int depth, bool is_max, Ui::Field player, Ui::Field opponent) {
    int score = eval(board, player, opponent);

    if (score == 10 || score == -10) {
        return score;
    }

    if (!is_move_left(board)) {
        return 0;
    }

    if (is_max) {
        int best = -1000;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == Ui::Field::None) {
                    board[i][j] = player;

                    best = max(best, minmax(board, depth++, !is_max, player, opponent));

                    board[i][j] = Ui::Field::None;
                }
            }
        }

        return best;
    } else {
        int best = 1000;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == Ui::Field::None) {
                    board[i][j] = opponent;
                    // moze to tutaj trzeba podmienic player z opponent
                    best = max(best, minmax(board, depth++, !is_max, player, opponent));

                    board[i][j] = Ui::Field::None;
                }
            }
        }

        return best;
    }
}

Move find_best_move(Ui::Field board[3][3], Ui::Field player, Ui::Field opponent) {
    int best_val = -1000;
    Move best_move;
    best_move.x = -1;
    best_move.y = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == Ui::Field::None) {
                board[i][j] = player;

                int move_val = minmax(board, 0, false, player, opponent);

                board[i][j] = Ui::Field::None;

                if (move_val > best_val) {
                    best_move.x = j;
                    best_move.y = i;

                    best_val = move_val;
                }
            }
        }
    }

    return best_move;
}
