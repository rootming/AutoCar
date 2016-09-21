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
#include "../config/data.h"

using namespace std;

void getServerAddr()
{}
int main(void)
{
    int socketFD;
    struct sockaddr_in clientAddr;
    uint8_t *buffer = new uint8_t[DEF_BUFFER_SIZE];

    ((PackageHead *)buffer)->length = DEF_BUFFER_SIZE - DEF_HEAD_LENGTH;
    ((PackageHead *)buffer)->magic = DEF_MAGIC_NUM;
    ((PackageHead *)buffer)->command  = _CMD_POST;
    sprintf((char *)buffer + DEF_HEAD_LENGTH, "Hello server"); 

    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientAddr.sin_port = htons(DEF_SERVER_PORT);

    if((socketFD = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        cerr << "Socket create failed\n";
        exit(1);
    }

    if(connect(socketFD, (struct sockaddr *)&clientAddr, sizeof(struct sockaddr_in)) == -1){
            cerr << "Connect error.\n";
            exit(1);
    }

    while(1)
        write(socketFD, buffer, DEF_BUFFER_SIZE);
    close(socketFD);
    return 0;
}
