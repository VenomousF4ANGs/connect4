#include "HomeScene.h"
#include "../game/GameScene.h"
#include "../match_making/MatchMakingScene.h"
#include "../../drivers/touch/TouchDriver.h"

using namespace ax;

void HomeScene::playWithFriendLocal()
{
    GameScene* gameScene = utils::createInstance<GameScene>();
    gameScene->setFriendLocalDrivers();
    _director->pushScene(gameScene);
}

void HomeScene::playWithFriendServer()
{
    MatchMakingScene* matchMakingScene = utils::createInstance<MatchMakingScene>();
    matchMakingScene->initialize();
    _director->pushScene(matchMakingScene);
}

void HomeScene::playWithBot()
{
    GameScene* gameScene = utils::createInstance<GameScene>();
    gameScene->setBotDrivers();
    _director->pushScene(gameScene);
}

void HomeScene::playWithMatchMaking()
{
    MatchMakingScene* matchMakingScene = utils::createInstance<MatchMakingScene>();
    matchMakingScene->initialize();
    _director->pushScene(matchMakingScene);
}
