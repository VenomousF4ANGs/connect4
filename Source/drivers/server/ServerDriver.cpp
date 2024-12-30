#include "ServerDriver.h"
#include "ServerDto.h"
#include "../../utilities/websocket/WebSocketUtil.h"
#include <unistd.h>

using namespace ax;

bool ServerDriver::init()
{
    return true;
}

void ServerDriver::initialize(int turn, Node* scene, WebSocketUtil* connection)
{
    this->scene       = scene;
    this->driverState = ServerDriveState::fresh;
    this->playerId    = generatePlayerId();
    this->sequence    = 0;

    this->connection = connection;
    this->connection->registerReceiveData([this](const char* data) {
        this->receiveDataFromServer(data);
        return true;
    });

    this->connection->errorHandler = [this]() {
        this->cleanupTasks();
        this->dispatchError("Connection Error");
    };
}

void ServerDriver::registerMatchHandler(std::function<void(int turn)> matchHandler)
{
    this->matchHandler = matchHandler;
}

std::string ServerDriver::generatePlayerId()
{

    const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    std::string playerId;
    playerId.reserve(10);

    for (int i = 0; i < 10; ++i)
    {
        playerId += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return playerId;
}

void ServerDriver::playNextMove(int column)
{
    if (this->dispatchTap != nullptr)
    {
        this->dispatchTap(column);
    }

    if (this->dispatchDrop != nullptr)
    {
        this->dispatchDrop(column);
    }
}

void ServerDriver::setTurn(int turn)
{
    this->driverState = (turn == 1) ? ServerDriver::thinking : ServerDriver::wait;
    AXLOG("[NAG] Server Driver Turn %d", turn);
}
