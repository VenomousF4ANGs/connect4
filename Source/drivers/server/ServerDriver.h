#ifndef __SERVER_DRIVER_H__
#define __SERVER_DRIVER_H__

#include "axmol.h"
#include "ServerDto.h"
#include "../Driver.h"
#include "../../utilities/websocket/WebSocketUtil.h"

class ServerDriver : public GameDriver
{
    enum ServerDriveState
    {
        fresh,
        disconnect,
        search,
        thinking,
        wait,
    };

public:
    bool init() override;
    void acceptPlay(int column) override;
    void acceptMove(int column) override;
    void acceptTap(int column) override;
    void acceptEnd() override;
    void setTurn(int turn) override;

    void initialize(int turn, ax::Node* scene, WebSocketUtil* connection);

    void registerMatchHandler(std::function<void(int turn)> matchHandler);
    void startMatchMaking();
    void cancelMatchMaking();
    void cleanupTasks() override;

private:
    void playNextMove(int column);
    void receiveDataFromServer(const char* data);
    void receivePlay(ServerDto& dto);
    void receiveMatch(ServerDto& dto);
    bool receiveDisconnected(ServerDto& dto);
    bool receiveReconnected(ServerDto& dto);
    bool receiveEnd(ServerDto& dto);
    bool receiveError(ServerDto& dto);
    std::string generatePlayerId();
    bool validateDto(ServerDto& dto);
    void validateSequence(ServerDto& dto);
    void sendData(ServerDto* dto);

private:
    ax::Node* scene;
    ServerDriveState driverState;
    ServerDriveState tmpState;
    WebSocketUtil* connection;

    std::function<void(int turn)> matchHandler;

    std::string gameCode;
    std::string playerId;
    long sequence;
};

#endif