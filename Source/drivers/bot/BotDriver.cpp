#include "BotDriver.h"
#include <unistd.h>
#include "../../utilities/background/Background.hpp"

using namespace ax;

bool BotDriver::init()
{
    initializeMemory();
    return true;
}

void BotDriver::setTurn(int turn)
{
    this->driverState = (turn == 1) ? BotDriver::thinking : BotDriver::waiting;
    if (this->driverState == BotDriver::thinking)
    {
        playNextMove(-1);
        driverState = BotDriveState::waiting;
    }
}

void BotDriver::initialize(Node* scene)
{
    this->scene = scene;
}

void BotDriver::initializeMemory()
{
    boardState   = std::vector<std::vector<int>>(boardRows);
    boardGrounds = std::vector<int>(boardColumns);
    for (int i = 0; i < boardRows; i++)
    {
        boardState[i] = std::vector<int>(boardRows);
    }
}

void BotDriver::acceptPlay(int column)
{
    if (driverState == BotDriveState::waiting)
    {
        driverState = BotDriveState::thinking;
        playNextMove(column);
        driverState = BotDriveState::waiting;
    }
}

void BotDriver::playNextMove(int column)
{
    setBoardPiece(column, 2);
    if (hasCompletedSequence(column))
    {
        return;  // lost
    }
    elevateGround(column);

    runInBackground<int>([this]() { return calculateNextMove(); }, [this](int nextMove) {
        if (nextMove < 0)
        {
            return;  // draw
        }

        this->setBoardPiece(nextMove, 1);
        this->elevateGround(nextMove);

        if (this->dispatchTap != nullptr)
        {
            this->dispatchTap(nextMove);
        }

        if (this->dispatchDrop != nullptr)
        {
            this->dispatchDrop(nextMove);
        }
    });

    // std::thread worker([this]() {
    //     int nextMove = calculateNextMove();
    //     if (nextMove < 0)
    //     {
    //         return;  // draw
    //     }

    //     this->setBoardPiece(nextMove, 1);
    //     this->elevateGround(nextMove);

    //     auto scheduler = ax::Director::getInstance()->getScheduler();
    //     scheduler->performFunctionInCocosThread([this, nextMove]() {
    //         // Code to run on the main thread
    //         AXLOG("Background task completed!");
    //         if (this->dispatchTap != nullptr)
    //         {
    //             this->dispatchTap(nextMove);
    //         }

    //         if (this->dispatchDrop != nullptr)
    //         {
    //             this->dispatchDrop(nextMove);
    //         }
    //     });
    // });

    // worker.detach();
}

void BotDriver::setBoardPiece(int column, int turn)
{
    int row                 = boardGrounds[column];
    boardState[row][column] = turn;
}

void BotDriver::elevateGround(int column)
{
    boardGrounds[column] += 1;
}

bool BotDriver::isSlotAvailable(int column)
{
    return boardGrounds[column] <= 5;
}
