#ifndef __TOUCH_DRIVER_H__
#define __TOUCH_DRIVER_H__

#include "axmol.h"
#include "../Driver.h"

class TouchDriver : public GameDriver
{
    enum TouchDriveState
    {
        thinking = 0,
        waiting,
        tapped,
    };

public:
    bool init() override;
    void acceptPlay(int column) override;
    void acceptTap(int column) override {};
    void acceptMove(int column) override {};
    void acceptEnd() override {};
    void setTurn(int turn) override;

    void initialize(ax::EventDispatcher* dispatcher, ax::Node* node);
    void setBoardBoundaries(float left, float right, float discSize);

private:
    TouchDriveState driverState;

    const int boardRows    = 6;
    const int boardColumns = 7;

    int turn;
    float discSize;
    float boardLeft;
    float boardRight;

    void registerTouch(ax::EventDispatcher* dispatcher, ax::Node* node);
    void onTouchEnded(const std::vector<ax::Touch*>& touch, ax::Event* event);
    void onTouchStarted(const std::vector<ax::Touch*>& touch, ax::Event* event);
    void onTouchMoved(const std::vector<ax::Touch*>& touch, ax::Event* event);

    int getColumn(ax::Vec2* point);
    void printState(const char* extra);
};

#endif