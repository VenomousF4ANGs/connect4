#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "axmol.h"

template <typename T>
void runInBackground(std::function<T()> task, std::function<void(T data)> callback)
{

    std::thread worker([task, callback]() {
        auto data      = task();
        auto scheduler = ax::Director::getInstance()->getScheduler();
        scheduler->schedule([=](float) {
            AXLOG("Background task completed!");
            callback(data);
        }, scheduler, 0.0f, 0, 0.0f, false, "Return to main thread");
    });

    worker.detach();
}

#endif