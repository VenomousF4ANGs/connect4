#include "ServerDto.h"
#include "simdjson/simdjson.h"
#include "axmol.h"

std::string ServerDto::marshal()
{

    std::ostringstream serialized;
    serialized << "{";

    serialized << R"("type":        ")" << type << R"(",)";
    serialized << R"("gameCode":    ")" << gameCode << R"(",)";
    serialized << R"("playerId":    ")" << playerId << R"(",)";
    serialized << R"("message":     ")" << message << R"(",)";

    serialized << R"("column":       )" << column << ",";
    serialized << R"("sequence":     )" << sequence;

    serialized << "}";

    fullString = serialized.str();
    return fullString;
}

void ServerDto::unmarshal(std::string serialized)
{
    fullString = serialized;

    simdjson::dom::parser parser;
    simdjson::dom::element parsedData;
    simdjson::error_code error = parser.parse(serialized).get(parsedData);
    if (error)
    {
        return;
    }

    auto key_exists = [](const simdjson::dom::element& parsedData, const char* key) -> bool {
        simdjson::dom::element value;

        if (parsedData.at_key(key).get(value) == simdjson::SUCCESS)
        {
            return !value.is_null();
        }

        return false;
    };

    this->type     = key_exists(parsedData, "type") ? std::string(parsedData["type"]) : "";
    this->gameCode = key_exists(parsedData, "gameCode") ? std::string(parsedData["gameCode"]) : "";
    this->playerId = key_exists(parsedData, "playerId") ? std::string(parsedData["playerId"]) : "";
    this->message  = key_exists(parsedData, "message") ? std::string(parsedData["message"]) : "";
    this->column   = key_exists(parsedData, "column") ? int(parsedData["column"].get_int64()) : 0;
    this->sequence = key_exists(parsedData, "sequence") ? int(parsedData["sequence"].get_int64()) : 0;
}

void ServerDto::display()
{
    AXLOG("Full String: %s", fullString.c_str());
    AXLOG("Type: %s", type.c_str());
    AXLOG("GameCode: %s", gameCode.c_str());
    AXLOG("PlayerId: %s", playerId.c_str());
    AXLOG("Message: %s", message.c_str());
    AXLOG("Column: %d", column);
    AXLOG("Sequence: %d", sequence);
}

std::string ServerDto::MESSAGE_PLAY         = "PLAY";
std::string ServerDto::MESSAGE_MOVE         = "MOVE";
std::string ServerDto::MESSAGE_TAP          = "TAP";
std::string ServerDto::MESSAGE_GAME_END     = "GAME_END";
std::string ServerDto::MESSAGE_ERROR        = "ERROR";
std::string ServerDto::MESSAGE_MATCH_FIND   = "MATCH_FIND";
std::string ServerDto::MESSAGE_MATCH_CANCEL = "MATCH_CANCEL";
std::string ServerDto::MESSAGE_DISCONNECTED = "DISCONNECTED";
std::string ServerDto::MESSAGE_RECONNECTED  = "RECONNECTED";
std::string ServerDto::MESSAGE_GAME_WAIT    = "GAME_WAIT";
std::string ServerDto::MESSAGE_GAME_FOUND   = "GAME_FOUND";