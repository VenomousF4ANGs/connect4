#include "HomeScene.h"
using namespace ax;

bool HomeScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    initializeDistances();
    placeLogo();

    placeFriendLocalButton();
    placeFriendServerButton();
    placeMatchMakingButton();
    placeBotButton();
    placePopup();

    return true;
}
