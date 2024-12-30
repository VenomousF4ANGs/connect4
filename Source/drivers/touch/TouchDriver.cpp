#include "../Driver.h"
#include "TouchDriver.h"

using namespace ax;

bool TouchDriver::init()
{
    return true;
}

void TouchDriver::initialize(EventDispatcher* dispatcher, Node* node)
{
    registerTouch(dispatcher, node);
    // printState("Touch driver Initialized!!");
}

void TouchDriver::setBoardBoundaries(float left, float right, float discSize)
{
    this->boardLeft  = left;
    this->boardRight = right;
    this->discSize   = discSize;
}

void TouchDriver::registerTouch(EventDispatcher* dispatcher, Node* node)
{
    auto touchListener = EventListenerTouchAllAtOnce::create();

    touchListener->onTouchesBegan = AX_CALLBACK_2(TouchDriver::onTouchStarted, this);
    touchListener->onTouchesMoved = AX_CALLBACK_2(TouchDriver::onTouchMoved, this);
    touchListener->onTouchesEnded = AX_CALLBACK_2(TouchDriver::onTouchEnded, this);

    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, node);
    // printState("registerTouch!!");
}

void TouchDriver::onTouchStarted(const std::vector<ax::Touch*>& touch, ax::Event* event)
{
    // printState("in touch started 1");
    if (driverState == TouchDriveState::thinking)
    {
        bool success = false;
        if (dispatchTap != nullptr)
        {
            Vec2 location = touch[0]->getLocation();
            int column    = getColumn(&location);
            success       = dispatchTap(column);
        }
        driverState = success ? TouchDriveState::tapped : TouchDriveState::thinking;
    }
    // printState("in touch started");
}

void TouchDriver::onTouchEnded(const std::vector<ax::Touch*>& touch, ax::Event* event)
{
    if (driverState == TouchDriveState::tapped)
    {
        bool success = false;
        if (dispatchDrop != nullptr)
        {
            Vec2 location = touch[0]->getLocation();
            int column    = getColumn(&location);
            success       = dispatchDrop(column);
        }

        driverState = success ? TouchDriveState::waiting : TouchDriveState::thinking;
    }
}

void TouchDriver::onTouchMoved(const std::vector<ax::Touch*>& touch, ax::Event* event)
{
    // printState("in touch moved 1");
    if (driverState == TouchDriveState::tapped)
    {
        bool success = false;
        if (dispatchMove != nullptr)
        {
            Vec2 location = touch[0]->getLocation();
            int column    = getColumn(&location);
            success       = dispatchMove(column);
        }
    }
    // printState("in touch moved 2");
}

void TouchDriver::acceptPlay(int column)
{
    if (driverState == TouchDriveState::waiting)
    {
        driverState = TouchDriveState::thinking;
    }

    this->printState("Accept Play");
}

int TouchDriver::getColumn(Vec2* point)
{
    point->x   = clampf(point->x, this->boardLeft, this->boardRight);
    int column = round((point->x - this->boardLeft) / this->discSize);

    return column;
}

void TouchDriver::printState(const char* extra)
{
    AXLOG("[NAG] Player%d Message: %s , Driver State: %d", this->turn, extra, this->driverState);
}

void TouchDriver::setTurn(int turn)
{
    this->turn        = turn;
    this->driverState = (turn == 1) ? TouchDriveState::thinking : TouchDriveState::waiting;
    AXLOG("[NAG] Touch Driver Turn %d", turn);
    // printState("[Nag] Touch driver state");
}