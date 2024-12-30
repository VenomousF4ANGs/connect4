#include "BotDriver.h"

std::vector<int> BotDriver::maxOpenSequence(int column)
{
    int row                 = boardGrounds[column];
    int currentTurn         = boardState[row][column];
    std::vector<int> maxSeq = std::vector<int>(4);

    // vertical
    int count = 1;
    int i     = 1;
    int open  = 0;
    while (((row - i) >= 0) && (boardState[row - i][column] == currentTurn))
    {
        count++;
        i++;
    }

    if ((boardColumns - i) >= (sequence - count))  // && (count >= maxSeq))
    {
        maxSeq[0] = count;
    }

    // right
    count = 1;
    i     = 1;
    open  = 0;
    while (((column + i) < boardColumns) && (boardState[row][column + i] == currentTurn))
    {
        count++;
        i++;
    }
    while (((column + i) < boardColumns) && (boardState[row][column + i] == 0))
    {
        open++;
        i++;
    }

    // left
    i = 1;
    while (((column - i) >= 0) && (boardState[row][column - i] == currentTurn))
    {
        count++;
        i++;
    }
    while (((column - i) >= 0) && (boardState[row][column - i] == 0))
    {
        open++;
        i++;
    }

    // horizontal
    if (((open + count) >= sequence))  // && (count >= maxSeq))
    {
        maxSeq[1] = count;
    }

    // positive diagonal
    count = 1;
    i     = 1;
    open  = 0;
    // top right
    while (((row + i) < boardRows) && ((column + i) < boardColumns) && (boardState[row + i][column + i] == currentTurn))
    {
        count++;
        i++;
    }
    while (((row + i) < boardRows) && ((column + i) < boardColumns) && (boardState[row + i][column + i] == 0))
    {
        open++;
        i++;
    }
    // bottom left
    i = 1;
    while (((row - i) >= 0) && ((column - i) >= 0) && (boardState[row - i][column - i] == currentTurn))
    {
        count++;
        i++;
    }
    while (((row - i) >= 0) && ((column - i) >= 0) && (boardState[row - i][column - i] == 0))
    {
        open++;
        i++;
    }
    // positive diagonal
    if (((open + count) >= sequence))  // && (count >= maxSeq))
    {
        maxSeq[2] = count;
    }

    // negative diagonal
    count = 1;
    i     = 1;
    open  = 0;
    // bottom right
    while (((row + i) < boardRows) && ((column - i) >= 0) && (boardState[row + i][column - i] == currentTurn))
    {
        count++;
        i++;
    }
    while (((row + i) < boardRows) && ((column - i) >= 0) && (boardState[row + i][column - i] == 0))
    {
        open++;
        i++;
    }
    i = 1;
    // top left
    while (((row - i) >= 0) && ((column + i) < boardColumns) && (boardState[row - i][column + i] == currentTurn))
    {
        count++;
        i++;
    }
    while (((row - i) >= 0) && ((column + i) < boardColumns) && (boardState[row - i][column + i] == 0))
    {
        open++;
        i++;
    }
    if (((open + count) >= sequence))  // && (count >= maxSeq))
    {
        maxSeq[3] = count;
    }

    return maxSeq;
}

int BotDriver::calculateNextMove()
{
    int maxScore  = -10000000000;
    int maxScoreI = -1;
    for (int i = 0; i < boardColumns; i++)
    {
        if (isSlotAvailable(i))
        {
            auto score = evaluateColumn(i, 1, 1);
            if (score > maxScore)
            {
                maxScore  = score;
                maxScoreI = i;
            }

            AXLOG("SCORE %d %d", i, score);
        }
    }

    return maxScoreI;
}

int BotDriver::evaluateColumn(int column, int turn, int depth)
{

    if (depth > botDepth)
    {
        return 0;
    }

    int row   = boardGrounds[column];
    int score = 0;

    if (isSlotAvailable(column))
    {
        boardState[row][column] = turn;
        auto sequences          = maxOpenSequence(column);
        score                   = evaluateScore(sequences, turn);
        boardGrounds[column]    = boardGrounds[column] + 1;

        if (score > -1000 && score < 1000)
        {
            for (int i = 0; i < boardColumns; i++)
            {
                int nextScore = evaluateColumn(i, turn % 2 + 1, depth + 1);
                // nextScore     = depth > 2 ? nextScore / (depth - 1) : nextScore;
                nextScore /= depth;
                score += nextScore;
            }
        }
        else if (depth <= 2)
        {
            score *= 1000;
        }

        boardState[row][column] = 0;
        boardGrounds[column] -= 1;
    }

    return score;
}

int BotDriver::evaluateScore(std::vector<int> sequences, int turn)
{
    int score = 0;
    for (int seq : sequences)
    {
        if (seq >= 4)
        {
            score += 1000;
        }
        else
        {
            if (seq > 1)
            {
                score += seq;
            }
        }
    }

    return turn == 1 ? score : -score;
}

bool BotDriver::hasCompletedSequence(int column)
{
    auto sequences = maxOpenSequence(column);
    for (int seq : sequences)
    {
        if (seq >= 4)
        {
            return true;
        }
    }

    return false;
}
