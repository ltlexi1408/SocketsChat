#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <cstring>

#define PORT 8000

int main(){
    //creat socket
    int server, new_socket;
    char *message;

    if((server = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        return -1;
    }

    // create address
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    //binds socket
    if(bind(server, (struct sockaddr*)&address, sizeof(address)) < 0){
        return -2;
    }

    // starts listening for traffic
    if(listen(server, 5) < 0){
        return -3;
    }

    //
    if(new_socket = accept(server, nullptr, nullptr)< 0){
        return -4;
    }

    while(strcmp(message, "q") != 0){
        std::cin >> message;
        send(new_socket, message, strlen(message), 0);
    }


    close(new_socket);
    close(server);

    return 0;
}