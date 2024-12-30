#include "GameScene.h"
#include "../../utilities/button/Button.h"
#include "../../utilities/popup/Popup.h"
#include "AudioEngine.h"

using namespace ax;

void GameScene::initializeDistances()
{
    Vec2 visibleSize = _director->getVisibleSize();
    Vec2 origin      = _director->getVisibleOrigin();
    center           = Vec2(origin.x + visibleSize.width / 2 + centerOffset, origin.y + visibleSize.height / 2);

    const float boardHeight = (discSize * boardRows);
    const float boardWidth  = (discSize * boardColumns);

    boardLeft   = center.x - (boardWidth / 2) + (discSize / 2);
    boardRight  = center.x + (boardWidth / 2) - (discSize / 2);
    boardBottom = center.y - (boardHeight / 2) + (discSize / 2);

    xSteps = std::vector<float>(boardColumns);
    for (int i = 0; i < boardColumns; i++)
    {
        xSteps[i] = boardLeft + (i * (discSize));
    }

    ySteps = std::vector<float>(boardRows);
    for (int i = 0; i < boardRows; i++)
    {
        ySteps[i] = boardBottom + (i * (discSize));
    }
}

void GameScene::placeBoard()
{
    auto boardBack = Sprite::create("sprite/board_back.png");
    boardBack->setPosition(center);
    this->addChild(boardBack, -1);

    auto boardFront = Sprite::create("sprite/board_front.png");
    boardFront->setPosition(Vec2(center.x, center.y - 25));
    this->addChild(boardFront, 2);
}

void GameScene::updateCaption(const char* text)
{
    if (gameObject.currentCaption == nullptr)
    {
        Label* caption = Label::createWithTTF("Turn", "fonts/arial.ttf", 40);
        caption->setPosition(Vec2(center.x - labelOffset, center.y + 50));
        gameObject.currentCaption = caption;

        this->addChild(caption, 2);

        DrawNode* boundary = DrawNode::create();
        boundary->drawRect(Vec2(center.x - labelOffset - 150, center.y + 100),
                           Vec2(center.x - labelOffset + 150, center.y - 100), primaryColor, 5);

        this->addChild(boundary, 2);
    }

    gameObject.currentCaption->setString(text);
}

void GameScene::updateInstructions(const char* text)
{
    if (gameObject.currentInstruction == nullptr)
    {
        Label* instruction = Label::createWithTTF("Turn", "fonts/arial.ttf", 30);
        instruction->setPosition(Vec2(center.x - labelOffset, center.y + 200));
        instruction->setAlignment(TextHAlignment::CENTER);

        gameObject.currentInstruction = instruction;

        this->addChild(instruction, 2);

        DrawNode* boundary = DrawNode::create();
        boundary->drawRect(Vec2(center.x - labelOffset - 150, center.y + 250),
                           Vec2(center.x - labelOffset + 150, center.y + 150), primaryColor, 5);
        this->addChild(boundary, 2);
    }

    gameObject.currentInstruction->setString(text);
}

void GameScene::placeButton()
{
    Sprite* button = Sprite::create("sprite/main_menu.png");
    button->setPosition(Vec2(center.x - labelOffset, center.y - 200));
    this->addChild(button, 10);

    Button::registerAction(_eventDispatcher, button, [this] {
        this->onPlayerQuit();
        this->exitGame();
    }, true);
}

void GameScene::placeDisc(Vec2 point)
{

    if (gameObject.gameState == GameState::wait)
    {
        // gameObject.currentDisc =
        //     gameObject.turn == 1 ? Sprite::create("sprite/disc1.png") : Sprite::create("sprite/disc2.png");

        gameObject.currentDisc = gameObject.turn == 1
                                     ? Sprite::createWithSpriteFrame(gameObject.turnIndicator1->getSpriteFrame())
                                     : Sprite::createWithSpriteFrame(gameObject.turnIndicator2->getSpriteFrame());

        gameObject.currentDisc->setPosition(point);
        this->addChild(gameObject.currentDisc, 1);
    }
}

void GameScene::dropDisc(std::function<void(void)> callback)
{
    if (gameObject.currentDisc != nullptr)
    {
        Vec2 ground  = getGroundPoint();
        Rect discBox = gameObject.currentDisc->getBoundingBox();

        float discCenterY = (discBox.origin.y) + (discBox.size.y / 2);
        float distance    = (discCenterY - ground.y);
        float delay       = sqrt(distance) / (gravity);

        Vector<FiniteTimeAction*> dropActions = Vector<FiniteTimeAction*>();
        dropActions.pushBack(EaseIn::create(MoveBy::create(delay, Vec2(0, -distance)), easeCurve));
        dropActions.pushBack(CallFunc::create(
            [this, distance]() { AudioEngine::play2d("sound/drop.mp3", false, distance / 500, nullptr); }));

        while ((distance / restitution) > 1)
        {
            distance /= restitution;
            delay /= restitution;

            dropActions.pushBack(EaseOut::create(MoveBy::create(delay, Vec2(0, distance)), easeCurve));
            dropActions.pushBack(EaseIn::create(MoveBy::create(delay, Vec2(0, -distance)), easeCurve));
            dropActions.pushBack(CallFunc::create(
                [this, distance]() { AudioEngine::play2d("sound/drop.mp3", false, distance / 500, nullptr); }));
        }

        dropActions.pushBack(CallFunc::create(callback));
        gameObject.currentDisc->runAction(Sequence::create(dropActions));
        gameObject.currentDisc = nullptr;
    }
}

void GameScene::deleteDisc()
{
    if (gameObject.currentDisc != nullptr)
    {
        this->removeChild(gameObject.currentDisc, true);
        gameObject.currentDisc = nullptr;
    }
}

void GameScene::updateTurnIndicator()
{
    if (gameObject.turnIndicator1 == nullptr)
    {
        gameObject.turnIndicator1 = Sprite::createWithSpriteFrameName("disc1.png");
        gameObject.turnIndicator2 = Sprite::createWithSpriteFrameName("disc2.png");

        gameObject.turnIndicator1->setPosition(Vec2(center.x - labelOffset, center.y - 40));
        gameObject.turnIndicator2->setPosition(Vec2(center.x - labelOffset, center.y - 40));

        this->addChild(gameObject.turnIndicator1, 1);
        this->addChild(gameObject.turnIndicator2, 1);
    }

    if (gameObject.turn == 1)
    {
        gameObject.turnIndicator1->setVisible(true);
        gameObject.turnIndicator2->setVisible(false);
    }
    else
    {
        gameObject.turnIndicator1->setVisible(false);
        gameObject.turnIndicator2->setVisible(true);
    }
}

void GameScene::winningAnimation()
{
    Sequence* shine = Sequence::create(RotateBy::create(0.2, 720), DelayTime::create(1.8), nullptr);
    for (Node* disc : gameObject.winnerDiscs)
    {
        disc->runAction(RepeatForever::create(shine->clone()));
    }

    Sequence* beat =
        Sequence::create(ScaleBy::create(0.1, 1.5), ScaleBy::create(0.1, 1 / 1.5), DelayTime::create(0.8), nullptr);
    gameObject.currentCaption->runAction(RepeatForever::create(beat));
}

void GameScene::drawAnimation()
{
    Sequence* beat =
        Sequence::create(ScaleBy::create(0.1, 1.5), ScaleBy::create(0.1, 1 / 1.5), DelayTime::create(0.8), nullptr);
    gameObject.currentCaption->runAction(RepeatForever::create(beat));
}

Vec2 GameScene::getGroundPoint()
{
    int column = gameObject.currentColumn;
    int row    = gameObject.boardGrounds[column];

    return Vec2(xSteps[column], ySteps[row]);
}

Vec2 GameScene::getDiscPlacementPoint()
{
    int column = gameObject.currentColumn;

    return Vec2(xSteps[column], ySteps[boardRows - 1] + discSize);
}

const char* GameScene::getGameEndCaption()
{
    // logGameState();

    if (gameObject.winner == 3)
    {
        return "Draw!!";
    }
    else
    {

        switch (gameObject.gameType)
        {
        case GameType::FriendLocal:
            return "Winner!!";
            break;
        case GameType::Bot:
        case GameType::FriendOnline:
        case GameType::MatchMaking:
            return gameObject.winner == 1 ? "You Won!!" : "You Lost!!";
            break;
        }
    }
}

const char* GameScene::getGameRunningCaption()
{
    switch (gameObject.gameType)
    {
    case GameType::FriendLocal:
        return "Next Turn";
        break;
    case GameType::Bot:
        return gameObject.turn == 1 ? "Your Turn" : "Bot Thinking..";
        break;
    case GameType::MatchMaking:
    case GameType::FriendOnline:
        return gameObject.turn == 1 ? "Your Turn" : "Opponents Turn";
        break;
    }
}

const char* GameScene::getGameInstructions()
{
    if (gameObject.winner != 0)
    {
        return "Go back to main menu\nto start a new game";
    }

    switch (gameObject.gameType)
    {
    case GameType::Bot:
        return gameObject.turn == 1 ? "Tap on the board\nto drop your disc" : "Wait for the\Bot to play";
    case GameType::MatchMaking:
    case GameType::FriendOnline:
        return gameObject.turn == 1 ? "Tap on the board\nto drop your disc" : "Wait for your\nOpponent to play";
    case GameType::FriendLocal:
        return "Tap on the board\nto drop your disc";
        break;
    }
}

void GameScene::placePopup()
{
    popup = utils::createInstance<Popup>();
    popup->initialize(this);
    popup->retain();
}

void GameScene::exitGame()
{
    this->gameObject.player1->cleanupTasks();
    this->gameObject.player2->cleanupTasks();

    this->gameObject.player1->release();
    this->gameObject.player2->release();

    // this->popup->release();
    this->unscheduleAllCallbacks();

    this->_director->popScene();
}