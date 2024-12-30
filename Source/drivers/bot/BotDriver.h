#ifndef __BOT_DRIVER_H__
#define __BOT_DRIVER_H__

#include "axmol.h"
#include "../Driver.h"

class BotDriver : public GameDriver
{
    enum BotDriveState
    {
        thinking = 0,
        waiting,
    };

public:
    bool init() override;
    void acceptPlay(int column) override;
    void acceptTap(int column) override {};
    void acceptMove(int column) override {};
    void acceptEnd() override {};
    void setTurn(int turn) override;

    void initialize(ax::Node* scene);

private:
    void initializeMemory();
    void setBoardPiece(int column, int turn);
    void elevateGround(int column);
    bool isSlotAvailable(int column);
    std::vector<int> maxOpenSequence(int column);

    void playNextMove(int column);
    int calculateNextMove();

    int evaluateColumn(int column, int turn, int depth);
    int evaluateScore(std::vector<int> sequences, int turn);
    bool hasCompletedSequence(int column);

private:
    const int boardColumns = 7;
    const int boardRows    = 6;
    const int sequence     = 4;
    const int botDepth     = 8;

    ax::Node* scene;
    BotDriveState driverState;
    std::vector<std::vector<int>> boardState;
    std::vector<int> boardGrounds;
};

#endif