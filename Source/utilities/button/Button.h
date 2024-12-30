#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "axmol.h"
using namespace ax;

class Button
{
public:
    static void registerAction(EventDispatcher* dispatcher,
                               Node* node,
                               std::function<void()> action,
                               bool swallow = false);

    static void registerSwallow(EventDispatcher* dispatcher, Node* node, bool fullscreen = false);
};

#endif