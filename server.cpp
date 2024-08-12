#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8000

int main(){
    //creat socket
    int server, new_socket;

    if((server = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        return -1;
    }

    // create address
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    if(bind(server, (struct sockaddr*)&address, sizeof(address)) < 0){
        return -2;
    }

    if(listen(server, 5) < 0){
        return -3;
    }

    return 0;
}