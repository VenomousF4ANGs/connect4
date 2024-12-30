#ifndef __WEBSOCKET_UTIL_H__
#define __WEBSOCKET_UTIL_H__

#include <mutex>
#include "axmol.h"
#include "network/WebSocket.h"

class WebSocketUtil : public ax::network::WebSocket::Delegate
{
public:
    WebSocketUtil(const WebSocketUtil& obj) = delete;
    static WebSocketUtil* getConnection(const char* ip);

    void registerReceiveData(std::function<bool(const char* data)> target);
    void sendData(const char* data);
    void deactivate();
    void forceClose();

    std::function<void()> errorHandler;
    std::function<void()> connectedHandler;

private:
    WebSocketUtil()
    {
        retries    = 0;
        maxRetries = 100;
        active     = false;
    };

    void establishConnection(std::string ip);

    void onOpen(ax::network::WebSocket* ws) override;
    void onMessage(ax::network::WebSocket* ws, const ax::network::WebSocket::Data& data) override;
    void onClose(ax::network::WebSocket* ws) override;
    void onError(ax::network::WebSocket* ws, const ax::network::WebSocket::ErrorCode& error) override;

private:
    static WebSocketUtil* instance;
    static std::mutex mtx;

    std::function<bool(const char* data)> dataReceiver;
    ax::network::WebSocket* client;
    std::string ip;
    bool active;
    bool connected;
    int retries;
    int maxRetries;
};

#endif