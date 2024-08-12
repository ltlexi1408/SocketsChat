#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <cstring>

#define PORT 8000

int main(){
    int server;
    char *message;

    if((server = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        return -1;
    }

    // create address
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    if(connect(server, (struct sockaddr*)&address, sizeof(address)) < 0){
        return -2;
    }

    while(true){
        read(server, message, 1024);
        std::cout << *message << std::endl;
    }

    close(server);

    return 0;
}