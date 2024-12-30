
// #include "../Source/drivers/server/ServerDto.h"
#include "../Source/utilities/websocket/WebSocketUtil.h"

#include <iostream>

// void test_json()
// {
//     //  g++ -std=c++17 -I/Users/abhisekh.nag/code/axmol/3rdparty -o test_run ../axmol/3rdparty/simdjson/simdjson.cpp
//     //  Source/drivers/server/ServerDto.cpp Test/ServerDtoTest.cpp && ./test_run

//     ServerDto* data = new ServerDto();
//     data->unmarshal(
//         R"({
//                 "type": "END",
//                 "gameCode": "ABCD",
//                 "playerId": "PLAY",
//                 "message": "null",
//                 "column":5
//             })");
//     std::cout << data->marshal() << std::endl;
// }

void test_ws()
{
    // clang++ -std=c++17 -o test_run \
    // -I/Users/abhisekh.nag/code/axmol/3rdparty/robin-map/include \
    // -I/Users/abhisekh.nag/code/axmol/core \
    // -I/Users/abhisekh.nag/code/axmol/3rdparty/yasio \
    // -I/Users/abhisekh.nag/code/axmol/3rdparty/fmt/include \
    // ../axmol/core/network/WebSocket.cpp \
    // Source/utilities/websocket/WebSocketUtil.cpp \
    // Test/ServerDtoTest.cpp && \
    // ./test_run
}

int main()
{
    std::cout << "Test Run" << std::endl;

    return 0;
}