#include "Popup.h"
#include "../button/Button.h"

using namespace ax;

void Popup::initialize(Node* scene)
{
    this->scene    = scene;
    Vec2 sceneSize = scene->getContentSize();

    popupWindow = Sprite::create("sprite/popup.png");
    popupWindow->setPosition(Vec2(sceneSize.x / 2, sceneSize.y / 2));

    popupButton = Sprite::create("sprite/popup_button.png");
    popupButton->setPosition(Vec2(sceneSize.x / 2, sceneSize.y / 2 - 100));

    Vec2 windowSize = popupWindow->getContentSize();
    popupCaption    = Label::createWithTTF("Popup", "fonts/arial.ttf", 40);
    popupCaption->setPosition(Vec2(windowSize.x / 2, windowSize.y / 2 + 80));
    popupWindow->addChild(popupCaption, 12);

    scene->addChild(popupWindow, 10);
    scene->addChild(popupButton, 12);

    Button::registerAction(scene->getEventDispatcher(), popupButton, [this]() {
        this->popupButton->setVisible(false);
        this->popupWindow->setVisible(false);

        if (this->action != nullptr)
        {
            this->action();
            this->action = nullptr;
        }
    }, true);

    Button::registerSwallow(this->scene->getEventDispatcher(), popupWindow, true);

    popupButton->setVisible(false);
    popupWindow->setVisible(false);
}

void Popup::show(const char* text, std::function<void()> action)
{
    this->action = action;

    popupWindow->setVisible(true);
    popupButton->setVisible(true);

    AXLOG("Visibility : %d %d : %s", popupWindow->isVisible(), popupButton->isVisible(), text);

    popupCaption->setString(text);
    Vec2 sceneSize = scene->getContentSize();
    popupWindow->setPosition(Vec2(sceneSize.x / 2, sceneSize.y / 2));

    // this->scene->getEventDispatcher()->removeEventListenersForTarget(popupWindow, true);
    // this->scene->getEventDispatcher()->removeEventListenersForTarget(popupButton, true);
}
