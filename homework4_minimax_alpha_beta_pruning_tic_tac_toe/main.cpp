#include <iostream>
#include <algorithm>

using std::max;
using std::min;

struct Move
{
    int row, col;
};

class Board
{
public:
    constexpr static char PLAYER1_VALUE = 'x';
    constexpr static char PLAYER2_VALUE = 'o';
    constexpr static char EMPTY_CELL = '_';

    enum class Status
    {
        UNFINISHED, // game has not yet finished, there are still moves left
        PLAYER1_WINS,
        PLAYER2_WINS,
        TIE
    };

    bool isEmptyCell(int x, int y) const
    {
        return arr[x][y] == EMPTY_CELL;
    }

    void setCell(int x, int y, char value)
    {
        if (value != PLAYER1_VALUE && value != PLAYER2_VALUE && value != EMPTY_CELL)
            throw "Invalid value for cell!";

        arr[x][y] = value;
    }

    char getCell(int x, int y) const
    {
        return arr[x][y];
    }

    void print(std::ostream &os = std::cout) const
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                os << getCell(i, j) << ' ';
            }
            os << std::endl;
        }
    }

    static Board createBoard(char boardArr[3][3])
    {
        Board board;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                board.setCell(i, j, boardArr[i][j]);
            }
        }

        return board;
    }

    bool areThereAnyMovesLeft() const
    {
        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                if (arr[row][col] == EMPTY_CELL)
                    return true;
            }
        }

        return false;
    }

    Status getStatus() const
    {
        const int score = evaluate();
        switch (score)
        {
        case 10:
            return Status::PLAYER1_WINS;
        case -10:
            return Status::PLAYER2_WINS;
        default:
        {
            if (areThereAnyMovesLeft())
            {
                return Status::UNFINISHED;
            }
            else
            {
                return Status::TIE;
            }
        }
        }
    }

private:
    char arr[3][3];

private:
    // Create empty board
    Board()
    {
        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                arr[row][col] = EMPTY_CELL;
            }
        }
    }

    /**
     * Return a value based on who is winning
     *
     * If the player wins, return 10
     * If the opponent wins, return -10
     * If tie, return 0
     */
    int evaluate() const
    {
        // Check rows for victory
        for (int row = 0; row < 3; row++)
        {
            if (areAllValuesInRowAreEqual(row))
            {
                const int valueInRow = arr[row][0];
                if (valueInRow == PLAYER1_VALUE)
                    return 10;
                else if (valueInRow == PLAYER2_VALUE)
                    return -10;
            }
        }

        // Check columns for victory
        for (int col = 0; col < 3; col++)
        {
            if (areAllValuesInColumnAreEqual(col))
            {
                const int valueInColumn = arr[0][col];
                if (valueInColumn == PLAYER1_VALUE)
                    return 10;
                else if (valueInColumn == PLAYER2_VALUE)
                    return -10;
            }
        }

        // Check diagonals for victory
        if (areAllValuesInPrimaryDiagonalEqual() || areAllValuesInSecondaryDiagonalEqual())
        {
            const int valueInDiagonal = arr[1][1];
            if (valueInDiagonal == PLAYER1_VALUE)
                return 10;
            else if (valueInDiagonal == PLAYER2_VALUE)
                return -10;
        }

        // Tie
        return 0;
    }

    bool areAllValuesInPrimaryDiagonalEqual() const
    {
        return arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2];
    }

    bool areAllValuesInSecondaryDiagonalEqual() const
    {
        return arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0];
    }

    bool areAllValuesInRowAreEqual(int row) const
    {
        return arr[row][0] == arr[row][1] && arr[row][1] == arr[row][2];
    }

    bool areAllValuesInColumnAreEqual(int col) const
    {
        return arr[0][col] == arr[1][col] && arr[1][col] == arr[2][col];
    }
};

std::ostream &operator<<(std::ostream &os, const Board &board)
{
    board.print(os);
    return os;
}

int minimax(Board board, bool isMaxTurn, int alpha, int beta)
{
    switch (board.getStatus())
    {
    case Board::Status::PLAYER1_WINS:
    {
        return 10;
    }
    case Board::Status::PLAYER2_WINS:
    {
        return -10;
    }
    case Board::Status::TIE:
    {
        return 0;
    }
    case Board::Status::UNFINISHED:
    {
        if (isMaxTurn)
        {
            int best = -1000;

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (board.isEmptyCell(i, j))
                    {
                        // Make the move
                        board.setCell(i, j, Board::PLAYER1_VALUE);

                        // Call minimax recursively and choose the maximum value
                        best = max(best,
                                   minimax(board, !isMaxTurn, alpha, beta));
                        alpha = max(alpha, best);

                        // Undo the move
                        board.setCell(i, j, Board::EMPTY_CELL);

                        if (beta <= alpha) // no need to continue if there is already better option for the minimizer
                            return best;
                    }
                }
            }
            return best;
        }
        else // minimzer move
        {
            int best = 1000;

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (board.isEmptyCell(i, j))
                    {
                        // Make the move
                        board.setCell(i, j, Board::PLAYER2_VALUE);

                        // Call minimax recursively and choose the minimum value
                        best = min(best,
                                   minimax(board, !isMaxTurn, alpha, beta));
                        beta = min(beta, best);

                        // Undo the move
                        board.setCell(i, j, Board::EMPTY_CELL);

                        if (beta <= alpha) // no need to continue if there is already better option for the maximizer
                            return best;
                    }
                }
            }
            return best;
        }
    }
    }
}

// Given a board, finds the best possible move for player 1
Move findBestMove(Board board)
{
    int bestVal = -1000;
    Move bestMove{-1, -1};

    // Traverse all cells, evaluate minimax function for
    // all empty cells. And return the cell with optimal value.
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board.isEmptyCell(i, j))
            {
                // Make the move
                board.setCell(i, j, Board::PLAYER1_VALUE);

                // Compute evaluation function for this move
                int moveVal = minimax(board, false, -10000, +10000);

                // Undo the move
                board.setCell(i, j, Board::EMPTY_CELL);

                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    printf("The value of the best Move is : %d\n\n", bestVal);

    return bestMove;
}

int main()
{
    char boardArr[3][3] = {
        {'x', 'o', 'x'},
        {'o', 'o', 'x'},
        {'_', '_', '_'}};

    // char boardArr[3][3] = {
    // {'_', '_', '_'},
    // {'_', '_', '_'},
    // {'_', '_', '_'}};

    Board board = Board::createBoard(boardArr);

    Move bestMove = findBestMove(board);

    printf("The Optimal Move is :\n");
    printf("ROW: %d COL: %d\n\n", bestMove.row, bestMove.col);

    return 0;
}