#include "ServerDriver.h"
#include "ServerDto.h"
#include "../../utilities/websocket/WebSocketUtil.h"

// Receive

void ServerDriver::receiveDataFromServer(const char* data)
{
    ServerDto dto = {};
    dto.unmarshal(data);
    auto valid = validateDto(dto);
    if (!valid)
    {
        return;
    }

    auto error        = receiveError(dto);
    auto disconnected = receiveDisconnected(dto);
    auto reconnected  = receiveReconnected(dto);
    auto end          = receiveEnd(dto);

    if (error || disconnected || reconnected || end)
    {
        return;
    }

    switch (driverState)
    {
    case ServerDriveState::search:
        validateSequence(dto);
        receiveMatch(dto);
        break;
    case ServerDriveState::thinking:
        validateSequence(dto);
        receivePlay(dto);
        break;
    default:
        break;
    }
}

void ServerDriver::receiveMatch(ServerDto& dto)
{
    if (dto.type == ServerDto::MESSAGE_GAME_FOUND)
    {
        if (driverState == ServerDriveState::search)
        {
            gameCode = dto.gameCode;
            // AXLOG("[NAG] Match found Turn: %d", dto.column);
            matchHandler(dto.column);
        }
    }
    else if (dto.type == ServerDto::MESSAGE_GAME_WAIT)
    {
        if (driverState == ServerDriveState::search)
        {
            gameCode = dto.gameCode;
        }
    }
}

void ServerDriver::receivePlay(ServerDto& dto)
{
    bool success = false;
    if (dto.type == ServerDto::MESSAGE_PLAY)
    {
        if (this->dispatchDrop != nullptr)
        {
            success = this->dispatchDrop(dto.column);
        }

        driverState = success ? ServerDriveState::wait : driverState;
    }
    else if (dto.type == ServerDto::MESSAGE_MOVE)
    {
        if (this->dispatchMove != nullptr)
        {
            success = this->dispatchMove(dto.column);
        }
    }
    else if (dto.type == ServerDto::MESSAGE_TAP)
    {
        if (this->dispatchTap != nullptr)
        {
            success = this->dispatchTap(dto.column);
        }
    }
}

bool ServerDriver::receiveDisconnected(ServerDto& dto)
{
    if (dto.type == ServerDto::MESSAGE_DISCONNECTED)
    {
        AXLOG("[NAG] disconnected");
        tmpState    = driverState;
        driverState = ServerDriveState::disconnect;
        return true;
    }

    return false;
}

bool ServerDriver::receiveError(ServerDto& dto)
{
    if (dto.type == ServerDto::MESSAGE_ERROR)
    {
        AXLOG("[NAG] error : %s", dto.message.c_str());
        if (this->dispatchError != nullptr)
        {
            this->dispatchError(dto.message.c_str());
        }

        return true;
    }

    return false;
}

bool ServerDriver::receiveReconnected(ServerDto& dto)
{
    if (dto.type == ServerDto::MESSAGE_RECONNECTED)
    {
        if (driverState == ServerDriveState::disconnect)
        {
            AXLOG("[NAG] reconnected");
            driverState = tmpState;
        }

        return true;
    }

    return false;
}

bool ServerDriver::receiveEnd(ServerDto& dto)
{
    if (dto.type == ServerDto::MESSAGE_GAME_END)
    {
        if (this->dispatchEnd != nullptr)
        {
            return this->dispatchEnd();
        }
        return true;
    }

    return false;
}

// Send

void ServerDriver::startMatchMaking()
{
    if (driverState == ServerDriveState::fresh)
    {
        AXLOG("[NAG] start match making");
        ServerDto* data = new ServerDto();

        data->type     = ServerDto::MESSAGE_MATCH_FIND;
        data->playerId = playerId;

        driverState = ServerDriveState::search;
        sendData(data);
    }
}

void ServerDriver::cancelMatchMaking()
{
    if (driverState == ServerDriveState::search)
    {
        AXLOG("[NAG] cancel match making");
        ServerDto* data = new ServerDto();

        data->gameCode = gameCode;
        data->type     = ServerDto::MESSAGE_MATCH_CANCEL;
        data->playerId = playerId;

        driverState = ServerDriveState::fresh;
        sendData(data);
        this->cleanupTasks();
    }
}

void ServerDriver::acceptPlay(int column)
{
    if (driverState == ServerDriveState::wait)
    {
        // std::string columnStr = std::to_string(column);

        ServerDto* data = new ServerDto();
        data->type      = ServerDto::MESSAGE_PLAY;
        data->gameCode  = gameCode;
        data->playerId  = playerId;
        data->column    = column;

        driverState = ServerDriveState::thinking;
        sendData(data);
    }
}

void ServerDriver::acceptTap(int column)
{
    if (driverState == ServerDriveState::wait)
    {
        ServerDto* data = new ServerDto();

        data->type     = ServerDto::MESSAGE_TAP;
        data->gameCode = gameCode;
        data->playerId = playerId;
        data->column   = column;

        sendData(data);
    }
}

void ServerDriver::acceptMove(int column)
{
    if (driverState == ServerDriveState::wait)
    {
        ServerDto* data = new ServerDto();
        data->type      = ServerDto::MESSAGE_MOVE;
        data->gameCode  = gameCode;
        data->playerId  = playerId;
        data->column    = column;

        sendData(data);
    }
}

void ServerDriver::acceptEnd()
{
    ServerDto* data = new ServerDto();
    data->type      = ServerDto::MESSAGE_GAME_END;
    data->gameCode  = gameCode;
    data->playerId  = playerId;

    sendData(data);
}

// UTILITIES

bool ServerDriver::validateDto(ServerDto& dto)
{
    if (dto.type == "")
    {
        dto.display();
        // this->cleanupTasks();
        this->dispatchError("No type specified");
        return false;
    }

    return true;
}

void ServerDriver::validateSequence(ServerDto& dto)
{
    if (dto.sequence < sequence)
    {
        dto.display();
        // this->cleanupTasks();
        this->dispatchError("Sequence does not match");
        return;
    }

    sequence = dto.sequence;
}

void ServerDriver::sendData(ServerDto* dto)
{
    sequence++;
    dto->sequence = sequence;

    std::string marshalled = dto->marshal();
    this->connection->sendData(marshalled.c_str());
}

void ServerDriver::cleanupTasks()
{
    this->connection->deactivate();
    this->connection->forceClose();
}
