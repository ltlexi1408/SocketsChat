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
    char message[1024];

    if((server = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        std::cout << "Socket creation failed" << std::endl;
        return -1;
    }

    std::cout << "Created Socket" << std::endl;

    // create address
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    //binds socket
    if(bind(server, (struct sockaddr*)&address, sizeof(address)) < 0){
        std::cout << "Binding Socket failed" << std::endl;
        return -2;
    }

    std::cout << "Binded to socket" << std::endl;

    // starts listening for traffic
    if(listen(server, 5) < 0){
        std::cout << "Failed to listen on Socket" << std::endl;
        return -3;
    }

    std::cout << "Listening on socket" << std::endl;

    //
    int addlen = sizeof(address);
    if(new_socket = accept(server, (struct sockaddr*)&address, (socklen_t*)&addlen)< 0){
        std::cout << "Failed to accept connection" << std::endl;
        return -4;
    }

    std::cout << "Accepted connection" << std::endl;

    while(strcmp(message, "q") != 0){
        std::cin >> message;
        std::cout << "message: " << message << std::endl;
        send(new_socket, message, strlen(message), 0);
    }


    close(new_socket);
    close(server);

    return 0;
}