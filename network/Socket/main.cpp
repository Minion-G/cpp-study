#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


int main() {

    auto fd = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(31300);

    if(inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) != 1){
        perror("addr_in");
        close(fd);
        return 1;
    }

    if(bind(fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) <0 ){
        perror("bind");
        close(fd);
        return 1;
    }
    char buf[1024];
    sockaddr_in peer{};
    socklen_t peer_len = sizeof(peer);
    auto n =recvfrom(fd, buf, sizeof(buf), 0, reinterpret_cast<sockaddr*>(&peer), &peer_len);

    std::cout.write(buf, n);

    auto s = sendto(fd, buf, n, 0, reinterpret_cast<sockaddr*>(&peer), peer_len);
    close(fd);


    return 0;
}
