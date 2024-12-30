#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "../../drivers/Driver.h"
#include "../../drivers/server/ServerDriver.h"
#include "../../utilities/popup/Popup.h"
#include "axmol.h"
#include <vector>

class GameScene : public ax::Scene
{
    enum GameState
    {
        wait,
        tap,
        drop,
        end
    };

    enum GameType
    {
        FriendLocal,
        FriendOnline,
        MatchMaking,
        Bot,
    };

    struct GameObject
    {
        int me;
        int turn;
        int currentColumn;
        int currentTouchId;
        int winner;

        std::vector<std::vector<int>> boardState;
        std::vector<std::vector<Node*>> boardDiscs;
        std::vector<Node*> winnerDiscs;
        std::vector<int> boardGrounds;

        GameState gameState;
        GameType gameType;

        ax::Node* currentDisc;
        ax::Sprite* turnIndicator1;
        ax::Sprite* turnIndicator2;
        ax::Label* currentCaption;
        ax::Label* currentInstruction;

        GameDriver* player1;
        GameDriver* player2;
    };

public:
    bool init() override;

    void preloadGraphics();

    void setFriendOnlineDrivers(ServerDriver*);
    void setMatchMakingDrivers(ServerDriver*);
    void setFriendLocalDrivers();
    void setBotDrivers();

    void setTurn(int turn);
    void resetHandlers();

private:
    // Game
    void initializeState();
    void resetState();
    void toggleTurn();
    void setBoardPiece();
    void elevateGround();
    bool isSlotAvailable(int column);
    bool isGameComplete();
    bool isGameDraw();

    // UI - Board
    void placeBoard();
    // UI - Disc
    void placeDisc(ax::Vec2 point);
    void dropDisc(std::function<void(void)> callback);
    void deleteDisc();
    // UI - Caption
    const char* getGameEndCaption();
    const char* getGameRunningCaption();
    const char* getGameInstructions();
    void updateCaption(const char* text);
    void updateInstructions(const char* text);
    void updateTurnIndicator();
    void winningAnimation();
    void drawAnimation();
    void placeButton();
    void exitGame();
    void preloadAudio();
    void placePopup();
    // UI - Processors
    void initializeDistances();
    ax::Vec2 getGroundPoint();
    ax::Vec2 getDiscPlacementPoint();

    // Misc
    void logGameState();

    // Drivers
    void finalizeDrivers();
    bool onPlayerTap(int column);
    bool onPlayerMove(int column);
    bool onPlayerPlay(int column);
    bool onPlayerQuit();

private:
    const float gravity     = 50;
    const float restitution = 3;
    const float easeCurve   = 2.5;

    const float discSize   = 92;
    const int boardColumns = 7;
    const int boardRows    = 6;
    const int sequence     = 4;

    const float labelOffset        = 540;
    const float centerOffset       = 140;
    const ax::Color4B primaryColor = ax::Color4B(20, 120, 250, 255);
    const ax::Color3B clickColor   = ax::Color3B(50, 150, 250);

    float boardLeft;
    float boardRight;
    float boardBottom;

    ax::Vec2 center;
    std::vector<float> xSteps;
    std::vector<float> ySteps;

    GameObject gameObject;
    Popup* popup;
};

#endif  // __MAIN_SCENE_H__
