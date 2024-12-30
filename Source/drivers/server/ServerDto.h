#ifndef __SERVER_DTO_H__
#define __SERVER_DTO_H__

#include "simdjson/simdjson.h"

class ServerDto
{
public:
    static std::string MESSAGE_PLAY;
    static std::string MESSAGE_MOVE;
    static std::string MESSAGE_TAP;
    static std::string MESSAGE_GAME_END;
    static std::string MESSAGE_ERROR;
    static std::string MESSAGE_MATCH_FIND;
    static std::string MESSAGE_MATCH_CANCEL;
    static std::string MESSAGE_DISCONNECTED;
    static std::string MESSAGE_RECONNECTED;
    static std::string MESSAGE_GAME_WAIT;
    static std::string MESSAGE_GAME_FOUND;

public:
    std::string type;
    std::string gameCode;
    std::string playerId;
    std::string message;
    int sequence;
    int column;

    std::string marshal();
    void unmarshal(std::string);

    std::string fullString;

    void display();
};

#endif