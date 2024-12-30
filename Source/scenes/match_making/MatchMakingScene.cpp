#include "MatchMakingScene.h"
#include "../game/GameScene.h"
#include "../../drivers/server/ServerDriver.h"
#include "../../utilities/button/Button.h"
#include "../../utilities/popup/Popup.h"
#include "ui/UITextField.h"

using namespace ax;

bool MatchMakingScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    return true;
}

void MatchMakingScene::initialize()
{
    socketConnected = false;
    placePopup();
    initializeDistances();
    initializeState();
    placeMainMenuButton();
    placeIpBox();
}

void MatchMakingScene::placeMainMenuButton()
{
    Sprite* button = Sprite::create("sprite/main_menu.png");
    button->setPosition(Vec2(center.x - 200, center.y - 180));
    this->addChild(button, 5);

    Button::registerAction(_eventDispatcher, button, [this] {
        // AXLOG("Main Menu Button");
        this->popup->show("Are you Sure?", [this]() { this->exitScene(); });
    }, true);
}

void MatchMakingScene::initializeDistances()
{
    Vec2 visibleSize = _director->getVisibleSize();
    Vec2 origin      = _director->getVisibleOrigin();

    center = Vec2(origin.x + visibleSize.width / 2, origin.y + (visibleSize.height / 2));
}

void MatchMakingScene::initializeState()
{
    player2          = nullptr;
    matchMakingState = MatchMakingState::fresh;
}

void MatchMakingScene::placeCaption(std::string ipAddress)
{
    auto caption        = "Please wait while we search for an oponent [" + ipAddress + "]";
    Label* popupCaption = Label::createWithTTF(caption, "fonts/arial.ttf", 40);
    popupCaption->setPosition(Vec2(center.x, center.y + 150));
    this->addChild(popupCaption, 1);
}

void MatchMakingScene::placeLoader()
{
    Sprite* loader = Sprite::create("sprite/loader.png");
    loader->setPosition(Vec2(center.x, center.y));
    this->addChild(loader, 1);

    loader->runAction(
        RepeatForever::create(Sequence::create(RotateBy::create(0, 60), DelayTime::create(0.2), nullptr)));
}

void MatchMakingScene::placeIpBox()
{
    ipField = ui::TextField::create("IP Address", "fonts/arial.ttf", 40);
    ipField->setPosition(Vec2(center.x, center.y + 150));
    ipField->setEnabled(true);
    ipField->setHighlighted(true);
    // ipField->retain();

    this->addChild(ipField, 1);

    Sprite* button = Sprite::create("sprite/find.png");
    button->setPosition(Vec2(center.x + 200, center.y - 180));
    this->addChild(button, 5);
    // button->retain();

    Button::registerAction(_eventDispatcher, button, [this, button] {
        // this->getEventDispatcher()->removeEventListenersForTarget(button, true);
        button->setOpacity(100);
        this->ipField->setVisible(false);

        auto ipAddress = ipField->getString();

        this->placeCaption(std::string(ipAddress));
        this->placeLoader();

        this->initializeConnection(std::string(ipAddress).c_str(), [this]() { this->findGame(); });
    }, true);
}

void MatchMakingScene::initializeConnection(const char* ip, std::function<void()> callback)
{
    connection = WebSocketUtil::getConnection(ip);

    connection->errorHandler = [this]() {
        this->socketConnected = false;
        this->popup->show("Connection Error", [this]() { this->exitScene(); });
    };

    connection->connectedHandler = [this, callback]() {
        this->socketConnected          = true;
        this->connection->errorHandler = nullptr;
        callback();
    };
}

void MatchMakingScene::findGame()
{
    if (matchMakingState == MatchMakingState::fresh)
    {
        GameScene* gameScene = utils::createInstance<GameScene>();
        gameScene->retain();
        player2 = utils::createInstance<ServerDriver>();
        gameScene->setMatchMakingDrivers(player2);

        player2->registerMatchHandler([this, gameScene](int turn) {
            if (this->matchMakingState == MatchMakingState::wait)
            {
                this->matchMakingState = MatchMakingState::found;
                gameScene->setTurn(turn);
                gameScene->resetHandlers();

                // gameScene->release();
                this->_director->replaceScene(gameScene);
            }
        });

        player2->registerError([this](const char* message) {
            // AXLOG("1.Match Making Error Handler , %s", message);
            this->popup->show(message, [this]() { this->exitScene(); });
            return true;
        });

        player2->initialize(2, gameScene, connection);
        matchMakingState = MatchMakingState::wait;
        player2->startMatchMaking();
    }
}

void MatchMakingScene::placePopup()
{
    popup = utils::createInstance<Popup>();
    popup->initialize(this);
    popup->retain();
}

void MatchMakingScene::exitScene()
{
    if (socketConnected)
    {
        if (player2 != nullptr)
        {

            player2->cancelMatchMaking();
            player2->cleanupTasks();
        }
        else
        {
            this->connection->deactivate();
            this->connection->forceClose();
        }
    }

    this->unscheduleAllCallbacks();
    this->_director->popScene();
}