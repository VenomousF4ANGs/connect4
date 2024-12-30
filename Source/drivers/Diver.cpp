#include "Driver.h"

void GameDriver::registerTap(std::function<bool(int)> dispatchTap)
{
    this->dispatchTap = dispatchTap;
}

void GameDriver::registerPlay(std::function<bool(int)> dispatchDrop)
{
    this->dispatchDrop = dispatchDrop;
}

void GameDriver::registerMove(std::function<bool(int)> dispatchMove)
{
    this->dispatchMove = dispatchMove;
}

void GameDriver::registerEnd(std::function<bool()> dispatchEnd)
{
    this->dispatchEnd = dispatchEnd;
}

void GameDriver::registerError(std::function<bool(const char*)> dispatchError)
{
    this->dispatchError = dispatchError;
}

void GameDriver::setColor(int color)
{
    this->color = color;
}
