#include "GameScene.h"
#include "../../drivers/touch/TouchDriver.h"
#include "../../drivers/bot/BotDriver.h"
#include "../../drivers/server/ServerDriver.h"

using namespace ax;

void GameScene::finalizeDrivers()
{
    this->gameObject.player1->registerTap([this](int column) { return this->onPlayerTap(column); });
    this->gameObject.player1->registerMove([this](int column) { return this->onPlayerMove(column); });
    this->gameObject.player1->registerPlay([this](int column) { return this->onPlayerPlay(column); });
    this->gameObject.player1->registerEnd([this]() {
        this->popup->show("Game Ended by Opponent", [this]() { this->exitGame(); });
        return true;
    });

    this->gameObject.player2->registerTap([this](int column) { return this->onPlayerTap(column); });
    this->gameObject.player2->registerMove([this](int column) { return this->onPlayerMove(column); });
    this->gameObject.player2->registerPlay([this](int column) { return this->onPlayerPlay(column); });
    this->gameObject.player2->registerEnd([this]() {
        this->popup->show("Game Ended by Opponent", [this]() { this->exitGame(); });
        return true;
    });

    this->gameObject.player1->retain();
    this->gameObject.player2->retain();
}

void GameScene::setFriendLocalDrivers()
{
    TouchDriver* player1 = utils::createInstance<TouchDriver>();
    TouchDriver* player2 = utils::createInstance<TouchDriver>();

    player1->setBoardBoundaries(this->boardLeft, this->boardRight, this->discSize);
    player2->setBoardBoundaries(this->boardLeft, this->boardRight, this->discSize);

    player1->initialize(this->_eventDispatcher, this);
    player2->initialize(this->_eventDispatcher, this);

    this->gameObject.player1 = player1;
    this->gameObject.player2 = player2;

    finalizeDrivers();
    setTurn(1);
    this->gameObject.gameType = GameType::FriendLocal;
    updateCaption(getGameRunningCaption());
}

void GameScene::setFriendOnlineDrivers(ServerDriver* player2)
{
    TouchDriver* player1 = utils::createInstance<TouchDriver>();

    player1->setBoardBoundaries(this->boardLeft, this->boardRight, this->discSize);
    player1->initialize(this->_eventDispatcher, this);
    this->gameObject.player1 = player1;
    this->gameObject.player2 = player2;

    finalizeDrivers();
    this->gameObject.gameType = GameType::FriendOnline;
    updateCaption(getGameRunningCaption());
}

void GameScene::setMatchMakingDrivers(ServerDriver* player2)
{
    TouchDriver* player1 = utils::createInstance<TouchDriver>();

    player1->setBoardBoundaries(this->boardLeft, this->boardRight, this->discSize);
    player1->initialize(this->_eventDispatcher, this);
    this->gameObject.player1 = player1;
    this->gameObject.player2 = player2;

    finalizeDrivers();
    this->gameObject.gameType = GameType::MatchMaking;
    updateCaption(getGameRunningCaption());
}

void GameScene::setBotDrivers()
{
    TouchDriver* player1 = utils::createInstance<TouchDriver>();
    BotDriver* player2   = utils::createInstance<BotDriver>();

    player1->setBoardBoundaries(this->boardLeft, this->boardRight, this->discSize);

    player1->initialize(this->_eventDispatcher, this);
    player2->initialize(this);

    this->gameObject.player1 = player1;
    this->gameObject.player2 = player2;

    finalizeDrivers();
    setTurn(1);
    this->gameObject.gameType = GameType::Bot;
    updateCaption(getGameRunningCaption());
}

bool GameScene::onPlayerPlay(int column)
{
    if (gameObject.gameState == GameState::tap)
    {
        if (isSlotAvailable(column))
        {
            setBoardPiece();
            dropDisc([this, column]() {
                GameDriver* otherPlayer = gameObject.turn == 1 ? gameObject.player2 : gameObject.player1;
                if (isGameComplete())
                {
                    updateCaption(getGameEndCaption());
                    updateInstructions(getGameInstructions());
                    winningAnimation();

                    gameObject.gameState = GameState::end;
                }
                else if (isGameDraw())
                {
                    updateCaption("Draw");
                    updateInstructions("Go back to main menu\nto start a new game");
                    drawAnimation();
                }
                else
                {
                    toggleTurn();
                    updateTurnIndicator();
                    updateCaption(getGameRunningCaption());
                    elevateGround();

                    gameObject.gameState = GameState::wait;
                }

                otherPlayer->acceptPlay(column);
            });

            return true;
        }
        else
        {
            gameObject.gameState = GameState::wait;
            deleteDisc();
            return false;
        }
    }
    // logGameState();

    return false;
}

bool GameScene::onPlayerTap(int column)
{
    // logGameState();
    if (gameObject.gameState == GameState::wait)
    {

        gameObject.currentColumn = column;
        placeDisc(getDiscPlacementPoint());
        gameObject.gameState = GameState::tap;

        GameDriver* otherPlayer = gameObject.turn == 1 ? gameObject.player2 : gameObject.player1;
        otherPlayer->acceptTap(column);

        return true;
    }

    // logGameState();
    return false;
}

bool GameScene::onPlayerMove(int column)
{
    if (gameObject.gameState == GameState::tap)
    {
        if (column != gameObject.currentColumn)
        {
            gameObject.currentColumn = column;
            gameObject.currentDisc->setPosition(getDiscPlacementPoint());

            GameDriver* otherPlayer = gameObject.turn == 1 ? gameObject.player2 : gameObject.player1;
            otherPlayer->acceptMove(column);
        }
        return true;
    }

    return false;
}

bool GameScene::onPlayerQuit()
{
    gameObject.gameState    = GameState::end;
    GameDriver* otherPlayer = gameObject.turn == 1 ? gameObject.player2 : gameObject.player1;
    otherPlayer->acceptEnd();

    return true;
}

void GameScene::resetHandlers()
{
    switch (gameObject.gameType)
    {
    case GameType::FriendLocal:
    case GameType::Bot:
        break;
    case GameType::MatchMaking:
    case GameType::FriendOnline:
        gameObject.player2->registerError([this](const char* message) {
            // AXLOG("Game Driver error handler");
            this->popup->show(message, [this]() { this->exitGame(); });
            return true;
        });
    }
}
