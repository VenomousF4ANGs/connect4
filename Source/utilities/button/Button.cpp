#include "axmol.h"
#include "Button.h"

using namespace ax;

void Button::registerAction(EventDispatcher* dispatcher, Node* node, std::function<void()> action, bool swallow)
{
    EventListenerTouchAllAtOnce* touchListener = EventListenerTouchAllAtOnce::create();

    touchListener->onTouchesBegan = [node, swallow](const std::vector<ax::Touch*>& touch, ax::Event* event) {
        if ((node->isVisible()) && (node->getBoundingBox().containsPoint(touch[0]->getStartLocation())))
        {
            node->setScale(0.95);
            if (swallow)
            {
                event->stopPropagation();
            }
        }
    };
    touchListener->onTouchesMoved = [node](const std::vector<ax::Touch*>& touch, ax::Event* event) {};

    touchListener->onTouchesEnded = [node, action, swallow](const std::vector<ax::Touch*>& touch, ax::Event* event) {
        if ((node->isVisible()) && (node->getBoundingBox().containsPoint(touch[0]->getStartLocation())))
        {
            node->setScale(1);
            action();
            if (swallow)
            {
                event->stopPropagation();
            }
        }
    };

    // touchListener->retain();

    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, node);
}

void Button::registerSwallow(EventDispatcher* dispatcher, Node* node, bool fullscreen)
{
    EventListenerTouchAllAtOnce* touchListener = EventListenerTouchAllAtOnce::create();

    auto propagateAndSwallow = [node, fullscreen](const std::vector<ax::Touch*>& touch, ax::Event* event) {
        if ((node->isVisible()) && (fullscreen || node->getBoundingBox().containsPoint(touch[0]->getStartLocation())))
        {
            event->stopPropagation();
        }
    };

    touchListener->onTouchesBegan = propagateAndSwallow;
    touchListener->onTouchesMoved = propagateAndSwallow;
    touchListener->onTouchesEnded = propagateAndSwallow;

    // touchListener->retain();

    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, node);
}