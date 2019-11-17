#include <iostream>

class Move
{
private:
    int x, y;
};

enum class GameResult
{
    PLAYER_WINS,
    OPPONENT_WINS,
    DRAW
};

class Board
{
public:
    constexpr static char PLAYER_MOVE = 'x';
    constexpr static char OPPONENT_MOVE = 'o';
    constexpr static char EMPTY_MOVE = '_';

    static Board createEmptyBoard()
    {
        return Board();
    }

    bool areThereAnyMovesLeft() const
    {
        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                if (arr[row][col] == EMPTY_MOVE)
                    return true;
            }
        }

        return false;
    }

    GameResult whoWins() const
    {
        const int score = evaluate();
        switch (score)
        {
        case 10:
            return GameResult::PLAYER_WINS;
        case -10:
            return GameResult::OPPONENT_WINS;
        default:
            return GameResult::DRAW;
        }
    }

private:
    int arr[3][3];

private:
    // Create empty board
    Board()
    {
        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                arr[row][col] = EMPTY_MOVE;
            }
        }
    }

    /**
     * Return a value based on who is winning
     *
     * If the player wins, return 10
     * If the opponents wins, return -10
     * If draw, return 0
     */
    int evaluate() const
    {
        // Check rows for victory
        for (int row = 0; row < 3; row++)
        {
            if (areAllValuesInRowAreEqual(row))
            {
                const int valueInRow = arr[row][0];
                if (valueInRow == PLAYER_MOVE)
                    return 10;
                else if (valueInRow == OPPONENT_MOVE)
                    return -10;
            }
        }

        // Check columns for victory
        for (int col = 0; col < 3; col++)
        {
            if (areAllValuesInColumnAreEqual(col))
            {
                const int valueInColumn = arr[0][col];
                if (valueInColumn == PLAYER_MOVE)
                    return 10;
                else if (valueInColumn == OPPONENT_MOVE)
                    return -10;
            }
        }

        // Check diagonals for victory
        if (areAllValuesInPrimaryDiagonalEqual() || areAllValuesInSecondaryDiagonalEqual())
        {
            const int valueInDiagonal = arr[1][1];
            if (valueInDiagonal == PLAYER_MOVE)
                return 10;
            else if (valueInDiagonal == OPPONENT_MOVE)
                return -10;
        }

        // Draw
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

int main()
{
    std::cout << "Hello world!" << std::endl;
}