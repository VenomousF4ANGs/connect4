#ifndef __HOME_SCENE_H__
#define __HOME_SCENE_H__

#include "axmol.h"
#include "../../utilities/popup/Popup.h"

class HomeScene : public ax::Scene
{

public:
    bool init() override;

private:
    // navigation
    void playWithFriendLocal();
    void playWithFriendServer();
    void playWithMatchMaking();
    void playWithBot();

    // UI
    void initializeDistances();
    void placeLogo();
    void placeFriendLocalButton();
    void placeFriendServerButton();
    void placeMatchMakingButton();
    void placeBotButton();
    void placePopup();

private:
    const float buttonOffset = 120;
    ax::Vec2 center;
    Popup* popup;
};

#endif  // __HOME_SCENE_H__
