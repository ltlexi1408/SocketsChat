#include <iostream>
#include <sys/socket.h>

#define PORT 8000

int main(){
    // Create socket
    int server = socket(AF_INET, SOCK_STREAM, 0);

    //Check socket status
    if(server == -1){
        return 1;
    }

    return 0;
}