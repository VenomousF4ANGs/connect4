#include "HomeScene.h"
#include "../../utilities/button/Button.h"
#include "../../utilities/popup/Popup.h"

using namespace ax;

void HomeScene::initializeDistances()
{
    Vec2 visibleSize = _director->getVisibleSize();
    Vec2 origin      = _director->getVisibleOrigin();

    center = Vec2(origin.x + visibleSize.width / 2, origin.y + (visibleSize.height / 2) - 50);
}

void HomeScene::placeLogo()
{
    Sprite* logo = Sprite::create("sprite/logo.png");

    logo->setPosition(Vec2(center.x, center.y + 2 * buttonOffset + 70));
    logo->setScale(1.5);

    this->addChild(logo, 1);
}

void HomeScene::placeFriendLocalButton()
{
    Sprite* button = Sprite::create("sprite/button_friend_local.png");

    button->setPosition(Vec2(center.x - 2 * buttonOffset, center.y + buttonOffset));

    this->addChild(button, 1);

    Button::registerAction(_eventDispatcher, button, [this] {
        // AXLOG("Inside Friend Local Function");
        this->playWithFriendLocal();
    }, false);
}

void HomeScene::placeFriendServerButton()
{
    Sprite* button = Sprite::create("sprite/button_friend_server.png");

    button->setPosition(Vec2(center.x - 2 * buttonOffset, center.y - buttonOffset));

    this->addChild(button, 1);

    Button::registerAction(_eventDispatcher, button, [this] {
        // AXLOG("Inside Friend Server Function");
        this->playWithFriendServer();
    }, false);
}

void HomeScene::placeMatchMakingButton()
{
    Sprite* button = Sprite::create("sprite/button_match_making.png");

    button->setPosition(Vec2(center.x + 2 * buttonOffset, center.y + buttonOffset));

    this->addChild(button, 1);

    Button::registerAction(_eventDispatcher, button, [this] {
        // AXLOG("Inside Match Making Function");
        this->playWithMatchMaking();
    }, false);
}

void HomeScene::placeBotButton()
{
    Sprite* button = Sprite::create("sprite/button_bot.png");

    button->setPosition(Vec2(center.x + 2 * buttonOffset, center.y - buttonOffset));

    this->addChild(button, 1);

    Button::registerAction(_eventDispatcher, button, [this] {
        // AXLOG("[NAG] Inside Bot Function");
        this->playWithBot();
    }, false);
}

void HomeScene::placePopup()
{
    popup = utils::createInstance<Popup>();
    popup->initialize(this);
    popup->retain();
}
