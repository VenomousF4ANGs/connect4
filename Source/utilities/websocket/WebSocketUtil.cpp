#include "WebSocketUtil.h"
#include <mutex>

WebSocketUtil* WebSocketUtil::instance = nullptr;
std::mutex WebSocketUtil::mtx;

WebSocketUtil* WebSocketUtil::getConnection(const char* ip)
{
    std::lock_guard<std::mutex> lock(mtx);
    if (WebSocketUtil::instance == nullptr)
    {
        WebSocketUtil::instance = new WebSocketUtil();
    }

    WebSocketUtil::instance->establishConnection(ip);
    return WebSocketUtil::instance;
}

void WebSocketUtil::establishConnection(std::string ip)
{
    // hostMobile = "192.168.104.45";
    // hostWifi   = "192.168.0.192";
    // hostEmulator = "10.0.2.2";
    // hostLocal = "127.0.0.1";

    this->connected = false;
    this->active    = true;
    this->retries   = 0;
    this->ip        = ip;

    this->client = new ax::network::WebSocket();
    bool success = client->open(this, "ws://" + ip + ":1234/connect4");
}

void WebSocketUtil::deactivate()
{
    this->active  = false;
    this->retries = 0;
}

void WebSocketUtil::forceClose()
{
    std::lock_guard<std::mutex> lock(WebSocketUtil::mtx);

    this->active  = false;
    this->retries = 0;

    if (connected)
    {
        this->client->close();
    }
}

void WebSocketUtil::sendData(const char* data)
{
    AXLOG("Send Data: %s", data);
    this->client->send(data);
}

void WebSocketUtil::registerReceiveData(std::function<bool(const char* data)> target)
{
    this->dataReceiver = target;
}

void WebSocketUtil::onOpen(ax::network::WebSocket* ws)
{
    // AXLOG("Connection Opened");
    retries   = 0;
    connected = true;
    if (connectedHandler != nullptr)
    {
        connectedHandler();
    }
}

void WebSocketUtil::onMessage(ax::network::WebSocket* ws, const ax::network::WebSocket::Data& data)
{
    // AXLOG("Data Received %s", data.bytes);
    // AXLOG("Data Length %ld", data.len);

    auto modData = std::string(data.bytes).substr(0, data.len);
    AXLOG("Mod Data %s", modData.c_str());

    dataReceiver(modData.c_str());
}

void WebSocketUtil::onClose(ax::network::WebSocket* ws)
{
    this->connected = false;
    retries++;
    if (active && retries > maxRetries)
    {
        if (errorHandler != nullptr)
        {
            errorHandler();
        }
        return;
    }

    AXLOG("Connection Closed - Reconnecting");
    if (active)
    {
        establishConnection(ip);
    }
}

void WebSocketUtil::onError(ax::network::WebSocket* ws, const ax::network::WebSocket::ErrorCode& error)
{
    this->connected = false;
    retries++;
    if (active && retries > maxRetries)
    {
        if (errorHandler != nullptr)
        {
            errorHandler();
        }
        return;
    }

    // AXLOGD("Error was fired, error code: {} , Reconnecting", static_cast<int>(error));
    if (active)
    {
        establishConnection(ip);
    }
}
