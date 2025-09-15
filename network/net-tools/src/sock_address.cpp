#include "net_tools/sock_address.hpp"
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdexcept>


net_tools::SockAddress::SockAddress(const char *addr, uint16_t port)
        : mSockAddr(std::make_unique<sockaddr_in>())
{
    *mSockAddr = sockaddr_in{};
    mSockAddr->sin_family = AF_INET;
    mSockAddr->sin_port = htons(port);

    if (inet_pton(AF_INET, addr, &mSockAddr->sin_addr.s_addr) != 1){
        throw std::runtime_error("invalid IPv4 format");
    }
}

net_tools::SockAddress::SockAddress(uint32_t addr, uint16_t port)
        : mSockAddr(std::make_unique<sockaddr_in>())
{
    *mSockAddr = sockaddr_in{};
    mSockAddr->sin_family = AF_INET;
    mSockAddr->sin_port = htons(port);
    mSockAddr->sin_addr.s_addr = htonl(addr);
}

sockaddr *net_tools::SockAddress::get() const noexcept{
    return reinterpret_cast<sockaddr*>(mSockAddr.get());
}

socklen_t net_tools::SockAddress::len() const noexcept{
    return sizeof(*mSockAddr);
}
