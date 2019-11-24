#include <iostream>
#include <algorithm>
#include <fstream>

using std::max;
using std::min;

struct Move
{
    int row, col;
};

class Board
{
public:
    constexpr static char MAXIMIZER_VALUE = 'X';
    constexpr static char MINIMIZER_VALUE = 'O';
    constexpr static char EMPTY_CELL = '_';

    int getNumberOfEmptyCells() const
    {
        int emptyCells = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (isEmptyCell(i, j))
                    emptyCells++;
            }
        }
        return emptyCells;
    }

    bool isTerminal() const
    {
        if (getNumberOfEmptyCells() == 0)
        {
            return true;
        }

        for (int i = 0; i < 3; i++)
        {
            if (arr[i][0] != Board::EMPTY_CELL && areAllValuesInRowAreEqual(i))
            {
                return true;
            }

            if (arr[0][i] != Board::EMPTY_CELL && areAllValuesInColumnAreEqual(i))
            {
                return true;
            }
        }

        return arr[1][1] != Board::EMPTY_CELL &&
               (areAllValuesInPrimaryDiagonalEqual() || areAllValuesInSecondaryDiagonalEqual());
    }

    bool isEmptyCell(int x, int y) const
    {
        return arr[x][y] == EMPTY_CELL;
    }

    static bool isInBoard(int x, int y)
    {
        return 0 <= x && x <= 2 &&
               0 <= y && y <= 2;
    }

    void setCell(int x, int y, char value)
    {
        if (value != MAXIMIZER_VALUE && value != MINIMIZER_VALUE && value != EMPTY_CELL)
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

    static Board createEmptyBoard()
    {
        return Board();
    }

    /**
     * Return a value based on who is winning
     *
     * If the maximier wins, return (100-level of the board)
     * If the minimzer wins, return -(100-level of the board)
     * If it is a tie return 0
     */
    int evaluate(int depth) const
    {
        if (!isTerminal())
            throw "Calling evaluate on non-terminal board!";

        // Check rows for victory
        for (int row = 0; row < 3; row++)
        {
            if (arr[row][0] != Board::EMPTY_CELL && areAllValuesInRowAreEqual(row))
            {
                const int valueInRow = arr[row][0];
                if (valueInRow == MAXIMIZER_VALUE)
                    return 100 - depth;
                else if (valueInRow == MINIMIZER_VALUE)
                    return -(100 - depth);
            }
        }

        // Check columns for victory
        for (int col = 0; col < 3; col++)
        {
            if (arr[0][col] != Board::EMPTY_CELL && areAllValuesInColumnAreEqual(col))
            {
                const int valueInColumn = arr[0][col];
                if (valueInColumn == MAXIMIZER_VALUE)
                    return 100 - depth;
                else if (valueInColumn == MINIMIZER_VALUE)
                    return -(100 - depth);
            }
        }

        // Check diagonals for victory
        if (arr[1][1] != Board::EMPTY_CELL && areAllValuesInPrimaryDiagonalEqual() || areAllValuesInSecondaryDiagonalEqual())
        {
            const int valueInDiagonal = arr[1][1];
            if (valueInDiagonal == MAXIMIZER_VALUE)
                return 100 - depth;
            else if (valueInDiagonal == MINIMIZER_VALUE)
                return -(100 - depth);
        }

        // Tie
        return 0;
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

int minimax(Board board, int depth, bool isMaxTurn, int alpha, int beta, std::ostream& logOs = std::cout)
{
    logOs << "\nST_TEST:\n"
              << board << std::endl;
    if (board.isTerminal())
    {
        logOs << "TERMINAL! depth: " << depth << "; evaluate: " << board.evaluate(depth) << "\n\n";
        return board.evaluate(depth);
    }

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
                    board.setCell(i, j, Board::MAXIMIZER_VALUE);

                    // Call minimax recursively and choose the maximum value
                    best = max(best,
                               minimax(board, depth + 1, !isMaxTurn, alpha, beta, logOs));
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
                    board.setCell(i, j, Board::MINIMIZER_VALUE);

                    // Call minimax recursively and choose the minimum value
                    best = min(best,
                               minimax(board, depth + 1, !isMaxTurn, alpha, beta, logOs));
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

// Given a board, finds the best possible move
Move findBestMove(Board board, bool isMaxTurn, std::ostream& logOs = std::cout)
{
    int bestVal = isMaxTurn ? -1000 : +1000;
    Move bestMove;

    // Traverse all cells, evaluate minimax function for
    // all empty cells. And return the cell with optimal value.
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board.isEmptyCell(i, j))
            {
                // Make the move
                board.setCell(i, j, isMaxTurn ? Board::MAXIMIZER_VALUE : Board::MINIMIZER_VALUE);

                // Compute evaluation function for this move
                int moveVal = minimax(board, 0, !isMaxTurn, -10000, +10000, logOs);

                // Undo the move
                board.setCell(i, j, Board::EMPTY_CELL);

                if ((isMaxTurn && moveVal > bestVal) ||
                    (!isMaxTurn && moveVal < bestVal))
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

int main()
{
    std::ofstream logFile;
    logFile.open("log.txt");

    std::string userInput;
    do
    {
        std::cout << "\nWant to play first? (y\\n): ";
        std::cin >> userInput;
    } while (userInput != "y" && userInput != "n");

    const auto userIsFirst = userInput == "y";

    auto board = Board::createEmptyBoard();

    if (!userIsFirst)
    {
        board.setCell(0, 0, Board::MINIMIZER_VALUE);
    }

    while (true)
    {
        std::cout << "\nCurrent board state: " << std::endl;
        board.print();

        int row, col;
        do
        {
            std::cout << "\nEnter your move - should be on an empty position on the board: ";
            std::cin >> row;
            std::cin >> col;
        } while (!Board::isInBoard(row, col) || board.getCell(row, col) != Board::EMPTY_CELL);

        board.setCell(row, col, Board::MAXIMIZER_VALUE);

        if (board.isTerminal())
        {
            break;
        }

        logFile << "\nFinding best move from this state:\n" << board << std::endl;
        Move bestMove = findBestMove(board, false, logFile); // AI is minimizer, hence false!
        logFile << "Best move is " << bestMove.row << " " << bestMove.col << std::endl;
        board.setCell(bestMove.row, bestMove.col, Board::MINIMIZER_VALUE);

        if (board.isTerminal())
        {
            break;
        }
    }

    std::cout << "\nGAME FINISHED!\n\nFinal board state:\n"
              << board << std::endl;

    const auto result = board.evaluate(0);
    if (result > 0)
    {
        std::cout << "Player wins!\n";
    }
    else if (result < 0)
    {
        std::cout << "AI wins!\n";
    }
    else
    {
        std::cout << "Tie!\n";
    }

    logFile.close();

    return 0;
}
