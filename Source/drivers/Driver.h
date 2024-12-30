#ifndef __DRIVER_INTERFACE__
#define __DRIVER_INTERFACE__

#include "axmol.h"

class GameDriver : public ax::Object
{

public:
    virtual bool init()                 = 0;
    virtual void acceptPlay(int column) = 0;
    virtual void acceptTap(int column)  = 0;
    virtual void acceptMove(int column) = 0;
    virtual void acceptEnd()            = 0;
    virtual void setTurn(int turn)      = 0;

    virtual void registerTap(std::function<bool(int)> dispatchTap);
    virtual void registerPlay(std::function<bool(int)> dispatchDrop);
    virtual void registerMove(std::function<bool(int)> dispatchMove);
    virtual void registerEnd(std::function<bool()> dispatchEnd);
    virtual void registerError(std::function<bool(const char*)> dispatchError);
    virtual void cleanupTasks() {};

protected:
    std::function<bool(int)> dispatchTap;
    std::function<bool(int)> dispatchDrop;
    std::function<bool(int)> dispatchMove;
    std::function<bool()> dispatchEnd;
    std::function<bool(const char*)> dispatchError;

    virtual void setColor(int color);
    int color;
};

#endif