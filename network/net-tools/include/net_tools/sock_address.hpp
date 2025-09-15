#pragma once
#include <memory>
#include <sys/socket.h>
#include <cstdint>

struct sockaddr_in;

namespace net_tools{
    class SockAddress {
    public:
        SockAddress(const char *addr, uint16_t port);
        SockAddress(uint32_t addr, uint16_t port);
        [[nodiscard]]sockaddr* get() const noexcept;
        [[nodiscard]]socklen_t len() const noexcept;
    private:
        std::unique_ptr<sockaddr_in> mSockAddr;

    };

    using SockAddressPtr = std::shared_ptr<SockAddress>;
}

