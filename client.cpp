#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <cstring>

#define PORT 8000

int main(){
    int server;
    char message[1024];

    if((server = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        std::cout << "Socket creation failed" << std::endl;
        return -1;
    }

    std::cout << "Created Socket" << std::endl;

    // create address
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    if(connect(server, (struct sockaddr*)&address, sizeof(address)) < 0){
        std::cout << "Failed to connect" << std::endl;
        return -2;
    }

    std::cout << "Connected to server" << std::endl;

    while(true){
        read(server, message, 1024);
        std::cout << message << std::endl;
    }

    close(server);

    return 0;
}