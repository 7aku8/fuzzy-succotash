#include<bits/stdc++.h>

#include "field.h"

using namespace std;

struct Move
{
    int y, x;
};

bool is_moves_left(Ui::Field board[3][3])
{
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            if (board[i][j]==Ui::Field::None)
                return true;
    return false;
}

int evaluate(Ui::Field b[3][3], Ui::Field player, Ui::Field opponent)
{
    // Checking for Rows for X or O victory.
    for (int row = 0; row<3; row++)
    {
        if (b[row][0]==b[row][1] &&
            b[row][1]==b[row][2])
        {
            if (b[row][0]==player)
                return +10;
            else if (b[row][0]==opponent)
                return -10;
        }
    }

    // Checking for Columns for X or O victory.
    for (int col = 0; col<3; col++)
    {
        if (b[0][col]==b[1][col] &&
            b[1][col]==b[2][col])
        {
            if (b[0][col]==player)
                return +10;

            else if (b[0][col]==opponent)
                return -10;
        }
    }

    // Checking for Diagonals for X or O victory.
    if (b[0][0]==b[1][1] && b[1][1]==b[2][2])
    {
        if (b[0][0]==player)
            return +10;
        else if (b[0][0]==opponent)
            return -10;
    }

    if (b[0][2]==b[1][1] && b[1][1]==b[2][0])
    {
        if (b[0][2]==player)
            return +10;
        else if (b[0][2]==opponent)
            return -10;
    }

    // Else if none of them have won then return 0
    return 0;
}

int minimax(Ui::Field board[3][3], int depth, bool isMax, Ui::Field player, Ui::Field opponent)
{
    int score = evaluate(board, player, opponent);

    // If Maximizer has won the game return his/her
    // evaluated score
    if (score == 10)
        return score;

    // If Minimizer has won the game return his/her
    // evaluated score
    if (score == -10)
        return score;

    // If there are no more moves and no winner then
    // it is a tie
    if (is_moves_left(board)==false)
        return 0;

    // If this maximizer's move
    if (isMax)
    {
        int best = -1000;

        // Traverse all cells
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Check if cell is empty
                if (board[i][j]==Ui::Field::None)
                {
                    // Make the move
                    board[i][j] = player;

                    // Call minimax recursively and choose
                    // the maximum value
                    best = max( best,
                        minimax(board, depth+1, !isMax, player, opponent) );

                    // Undo the move
                    board[i][j] = Ui::Field::None;
                }
            }
        }
        return best;
    }

    // If this minimizer's move
    else
    {
        int best = 1000;

        // Traverse all cells
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Check if cell is empty
                if (board[i][j]==Ui::Field::None)
                {
                    // Make the move
                    board[i][j] = opponent;

                    // Call minimax recursively and choose
                    // the minimum value
                    best = min(best,
                           minimax(board, depth+1, !isMax, player, opponent));

                    // Undo the move
                    board[i][j] = Ui::Field::None;
                }
            }
        }
        return best;
    }
}


Move findBestMove(Ui::Field board[3][3], Ui::Field player, Ui::Field opponent)
{
    int bestVal = -1000;
    Move bestMove;
    bestMove.y = -1;
    bestMove.x = -1;

    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            if (board[i][j]==Ui::Field::None)
            {
                board[i][j] = player;

                int moveVal = minimax(board, 2, false, player, opponent);

                board[i][j] = Ui::Field::None;

                if (moveVal > bestVal)
                {
                    bestMove.y = i;
                    bestMove.x = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}
