
#include "GameScene.h"
#include "../../drivers/Driver.h"
#include "AudioEngine.h"

using namespace ax;

bool GameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // Game states
    initializeState();
    resetState();

    // UI components
    preloadGraphics();
    initializeDistances();
    placeBoard();
    updateCaption(getGameRunningCaption());
    updateInstructions(getGameInstructions());
    updateTurnIndicator();
    placeButton();
    preloadAudio();
    placePopup();

    return true;
}

void GameScene::preloadGraphics()
{
    auto spritecache = SpriteFrameCache::getInstance();
    spritecache->addSpriteFramesWithFile("sprite/disc.plist");
}

void GameScene::preloadAudio()
{
    AudioEngine::preload("sound/drop.mp3", [](bool success) {});
}

void GameScene::initializeState()
{
    gameObject              = {};
    gameObject.boardState   = std::vector<std::vector<int>>(boardRows);
    gameObject.boardDiscs   = std::vector<std::vector<Node*>>(boardRows);
    gameObject.boardGrounds = std::vector<int>(boardColumns);
    for (int i = 0; i < boardRows; i++)
    {
        gameObject.boardState[i] = std::vector<int>(boardRows);
        gameObject.boardDiscs[i] = std::vector<Node*>(boardRows);
    }
}

void GameScene::resetState()
{
    gameObject.turn          = 1;
    gameObject.gameState     = GameState::wait;
    gameObject.currentDisc   = nullptr;
    gameObject.currentColumn = -1;
    gameObject.winner        = 0;

    for (int i = 0; i < boardRows; i++)
    {
        for (int j = 0; j < boardColumns; j++)
        {
            gameObject.boardState[i][j] = 0;
            gameObject.boardDiscs[i][j] = nullptr;

            gameObject.boardGrounds[j] = 0;
        }
    }
}

void GameScene::toggleTurn()
{
    gameObject.turn = gameObject.turn == 1 ? 2 : 1;
}

void GameScene::setBoardPiece()
{
    int column = gameObject.currentColumn;
    int row    = gameObject.boardGrounds[column];

    gameObject.boardState[row][column] = gameObject.turn;
    gameObject.boardDiscs[row][column] = gameObject.currentDisc;
}

void GameScene::elevateGround()
{
    int column = gameObject.currentColumn;
    gameObject.boardGrounds[column] += 1;
}

bool GameScene::isSlotAvailable(int column)
{
    return gameObject.boardGrounds[column] < boardRows;
}

bool GameScene::isGameComplete()
{

    int column      = gameObject.currentColumn;
    int row         = gameObject.boardGrounds[column];
    int currentTurn = gameObject.boardState[row][column];

    // AXLOG("%d %d %d", row, column, currentTurn);
    gameObject.winnerDiscs = std::vector<Node*>();
    gameObject.winnerDiscs.push_back(gameObject.boardDiscs[row][column]);

    // vertical
    int count = 1;
    int i     = 1;
    while (((row - i) >= 0) && (gameObject.boardState[row - i][column] == currentTurn))
    {
        count++;
        i++;
    }
    if (count >= sequence)
    {
        AXLOG("Winner Vertical");
        gameObject.winner = currentTurn;
        i--;
        while (((row - i) < boardRows) && (gameObject.boardState[row - i][column] == currentTurn))
        {
            gameObject.winnerDiscs.push_back(gameObject.boardDiscs[row - i][column]);
            i--;
        }
        return true;
    }

    // horizontal
    count = 1;
    i     = 1;
    while (((column + i) < boardColumns) && (gameObject.boardState[row][column + i] == currentTurn))
    {
        count++;
        i++;
    }
    i = 1;
    while (((column - i) >= 0) && (gameObject.boardState[row][column - i] == currentTurn))
    {
        count++;
        i++;
    }
    if (count >= sequence)
    {
        AXLOG("Winner Horizontal");
        gameObject.winner = currentTurn;

        i--;
        while (((column - i) < boardColumns) && (gameObject.boardState[row][column - i] == currentTurn))
        {
            gameObject.winnerDiscs.push_back(gameObject.boardDiscs[row][column - i]);
            i--;
        }

        return true;
    }

    // positive diagonal
    count = 1;
    i     = 1;
    while (((row + i) < boardRows) && ((column + i) < boardColumns) &&
           (gameObject.boardState[row + i][column + i] == currentTurn))
    {
        count++;
        i++;
    }
    i = 1;
    while (((row - i) >= 0) && ((column - i) >= 0) && (gameObject.boardState[row - i][column - i] == currentTurn))
    {
        count++;
        i++;
    }

    if (count >= sequence)
    {
        AXLOG("Winner +Diagonal");
        gameObject.winner = currentTurn;

        i--;
        while (((row - i) < boardRows) && ((column - i) < boardColumns) &&
               (gameObject.boardState[row - i][column - i] == currentTurn))
        {
            gameObject.winnerDiscs.push_back(gameObject.boardDiscs[row - i][column - i]);
            i--;
        }

        return true;
    }

    // negative diagonal
    count = 1;
    i     = 1;
    while (((row + i) < boardRows) && ((column - i) >= 0) &&
           (gameObject.boardState[row + i][column - i] == currentTurn))
    {
        count++;
        i++;
    }
    i = 1;
    while (((row - i) >= 0) && ((column + i) < boardColumns) &&
           (gameObject.boardState[row - i][column + i] == currentTurn))
    {
        count++;
        i++;
    }
    if (count >= sequence)
    {
        AXLOG("Winner -Diagonal");
        gameObject.winner = currentTurn;

        i--;
        while (((row - i) < boardRows) && ((column + i) >= 0) &&
               (gameObject.boardState[row - i][column + i] == currentTurn))
        {
            gameObject.winnerDiscs.push_back(gameObject.boardDiscs[row - i][column + i]);
            i--;
        }

        return true;
    }

    return false;
}

bool GameScene::isGameDraw()
{

    for (int i = 0; i < boardColumns; i++)
    {
        if (isSlotAvailable(i))
        {
            return false;
        }
    }

    gameObject.winner = 3;
    return true;
}

void GameScene::logGameState()
{
    AXLOG("[NAG] Game: CurrentColumn: %d CurrentTurn: %d ", gameObject.currentColumn, gameObject.turn);
    AXLOG("[NAG] Game: Winner: %d, State: %d, Me: %d", gameObject.winner, gameObject.gameState, gameObject.me);

    // AXLOG("[NAG] Board:");
    // for (int i = boardRows - 1; i >= 0; i--)
    // {
    //     AXLOG(" %d %d %d %d %d %d %d ", gameObject.boardState[i][0], gameObject.boardState[i][1],
    //           gameObject.boardState[i][2], gameObject.boardState[i][3], gameObject.boardState[i][4],
    //           gameObject.boardState[i][5], gameObject.boardState[i][6]);
    // }

    // AXLOG("[NAG] Grounds:");
    // AXLOG(" %d %d %d %d %d %d %d ", gameObject.boardGrounds[0], gameObject.boardGrounds[1],
    // gameObject.boardGrounds[2],
    //       gameObject.boardGrounds[3], gameObject.boardGrounds[4], gameObject.boardGrounds[5],
    //       gameObject.boardGrounds[6]);
}

void GameScene::setTurn(int turn)
{
    this->gameObject.me   = turn;
    this->gameObject.turn = turn;
    this->gameObject.player1->setTurn(turn);
    this->gameObject.player2->setTurn(turn == 1 ? 2 : 1);

    if (turn == 2)
    {
        auto tmp                  = gameObject.turnIndicator1;
        gameObject.turnIndicator1 = gameObject.turnIndicator2;
        gameObject.turnIndicator2 = tmp;
    }

    updateCaption(getGameRunningCaption());
    updateInstructions(getGameInstructions());
}