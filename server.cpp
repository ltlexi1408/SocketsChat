#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <cstring>

#include <cerrno>

#define PORT 8080

int main(){
    //creat socket
    int server, new_socket;
    char message[1024] = "hello world";

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

    //binds socket
    if(bind(server, (struct sockaddr*)&address, sizeof(address)) < 0){
        std::cerr << "Binding Socket failed" << strerror(errno) << std::endl;
        return -2;
    }

    std::cout << "Binded to socket" << std::endl;

    // starts listening for traffic
    if(listen(server, 5) < 0){
        std::cerr << "Failed to listen on Socket" << strerror(errno) << std::endl;
        return -3;
    }

    std::cout << "Listening on socket" << std::endl;

    //
    socklen_t addlen = sizeof(address);
    new_socket = accept(server, (struct sockaddr*)&address, &addlen);

    if(new_socket < 0){
         std::cerr << "Failed to accept connection: " << strerror(errno) << std::endl;
        return -4;
    }

    std::cout << "Accepted connection" << std::endl;

    while(strcmp(message, "q") != 0){
        memset(message, 0, sizeof(message));
        std::cin >> message;
        std::cout << "message: " << message << std::endl;
        if(send(new_socket, message, strlen(message), 0) < 0){
            std::cerr << "Failed to send message" << strerror(errno) << std::endl;
            return -5;
        }
    }

    close(new_socket);
    close(server);

    return 0;
}