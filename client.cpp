#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <cstring>

#include <cerrno>

#define PORT 8080

int main(){
    int server;
    char message[1024] = {0};

    if((server = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        std::cerr << "Socket creation failed" << strerror(errno) << std::endl;
        return -1;
    }

    std::cout << "Created Socket" << std::endl;

    // create address
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    if(connect(server, (struct sockaddr*)&address, sizeof(address)) < 0){
        std::cerr << "Failed to connect" << strerror(errno) << std::endl;
        return -2;
    }

    std::cout << "Connected to server" << std::endl;

    while(true){
    int reciev = read(server, message, 1024);
        if(reciev < 0){
            std::cerr << "Failed to Recive message" << strerror(errno) << std::endl;
            return -3;
        }else if(reciev == 0){
            std::cerr << "EOF" << strerror(errno) << std::endl;
            close(server);
            return 0;
        }
        std::cout << message << std::endl;
        memset(message, 0, sizeof(message));
    }

    close(server);

    return 0;
}