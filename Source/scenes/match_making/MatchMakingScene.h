#ifndef __MATCH_MAKING_SCENE_H__
#define __MATCH_MAKING_SCENE_H__

#include "axmol.h"
#include "../../utilities/popup/Popup.h"
#include "../../drivers/server/ServerDriver.h"
#include "ui/UITextField.h"

class MatchMakingScene : public ax::Scene
{
    enum MatchMakingState
    {
        fresh,
        wait,
        found
    };

public:
    bool init() override;
    void initialize();
    void placeMainMenuButton();

private:
    void initializeDistances();
    void initializeState();
    void placeCaption(std::string ipAddress);
    void placeLoader();
    void findGame();
    void placePopup();
    void placeIpBox();
    void initializeConnection(const char* ip, std::function<void()> callback);

    void exitScene();

private:
    ax::Vec2 center;
    MatchMakingState matchMakingState;
    Popup* popup;
    ServerDriver* player2;
    ax::ui::TextField* ipField;

    WebSocketUtil* connection;
    bool socketConnected;
};

#endif