#pragma once

#include "INetworkPAL.h"

#include <netinet/in.h>

namespace MoonCrawler {
enum class State {
    Client,
    Server
};

class NetworkLinuxPAL : public INetworkPAL {
    public:
    void initServer(std::filesystem::path configFile) override;
    void initServer(const std::string& host, unsigned short port) override;
    void initClient(std::filesystem::path configFile) override;
    void initClient(const std::string& host, uint64_t port) override;
    void sendData(const char* data) const override;
    void setReceiveCallback(void* instance, DataReceiveCallback callback) override;

    ~NetworkLinuxPAL();
    private:
    int m_sockfd{};
    bool m_isInitialized{false};
    bool m_isConnected{false};
    struct sockaddr_in m_servaddr, m_cliaddr;
    static constexpr uint16_t MAX_BUFFER_SIZE = 1024;
    std::array<char, MAX_BUFFER_SIZE> m_buffer{};
    DataReceiveCallback m_callback{};
    void* m_instance{};

    State m_state{};
};
}