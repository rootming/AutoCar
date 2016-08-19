#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include "data.h"

using namespace std;

void getServerAddr()
{}
int main(void)
{
    int socketFD;
    struct sockaddr_in clientAddr;
    uint8_t *buffer = new uint8_t[_BUFFER_SIZE];

    ((PackageHead *)buffer)->length = _BUFFER_SIZE - _HEAD_LENGTH;
    ((PackageHead *)buffer)->magic = _MAGIC_NUM;
    ((PackageHead *)buffer)->command  = _CMD_POST;
    sprintf((char *)buffer + _HEAD_LENGTH, "Hello server"); 

    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientAddr.sin_port = htons(_SERVER_PORT);

    if((socketFD = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        cerr << "Socket create failed\n";
        exit(1);
    }

    if(connect(socketFD, (struct sockaddr *)&clientAddr, sizeof(struct sockaddr_in)) == -1){
            cerr << "Connect error.\n";
            exit(1);
    }

    while(1)
        write(socketFD, buffer, _BUFFER_SIZE);
    close(socketFD);
    return 0;
}
