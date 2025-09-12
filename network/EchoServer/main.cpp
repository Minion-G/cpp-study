#include <iostream>
#include <vector>
#include "csignal"
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "unistd.h"

int main() {
    std::signal(SIGPIPE, SIG_IGN);

    int fd_Listen = ::socket(AF_INET, SOCK_STREAM, 0);
    if(fd_Listen < 0){
        perror("socket");
        return 1;
    }

    int yes = 1;
    if(setsockopt(fd_Listen, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0){
        perror("setSockOpt(SO_REUSEADDR");
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(31300);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(fd_Listen, (sockaddr*)&addr, sizeof(addr)) < 0){
        perror("bind");
        close(fd_Listen);
        return 1;
    }

    if(listen(fd_Listen, SOMAXCONN) < 0){
        perror("listen");
        close(fd_Listen);
        return 1;
    }

    std::cout << "listening on 0.0.0.0:31300\n";
    bool run = 1;
    std::vector<char>buf(1024);
    while (run){
        sockaddr_in cli{};
        socklen_t len = sizeof(cli);
        int fd = accept(fd_Listen, (sockaddr*)&cli, &len);
        if(fd < 0){
            perror("accept");
            continue;
        }
        for(;;){

            ssize_t n = recv(fd, buf.data(), buf.size(), 0);
            if(n > 0){
                ssize_t sent = send(fd, buf.data(), (size_t)n, 0);
                (void)sent;
            }
            std::string msg(buf.begin(), buf.begin()+4);
            if(msg== "exit"){
                run = 0;
                break;
            }

        }
        shutdown(fd, SHUT_WR);
        close(fd);
    }
    close(fd_Listen);
    return 0;
}
