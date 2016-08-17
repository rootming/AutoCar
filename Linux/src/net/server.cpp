#include <error.h>
#include "server.h"
#include "data.h"

using namespace std;

//static const char *defalutInterface = "eth1";

bool Server::getAddress(const string &interface, string &ip)
{
    struct ifaddrs *ifAddrStruct = NULL;
    void * tmpAddrPtr = NULL;
    bool found = false;
    getifaddrs(&ifAddrStruct);
    while (ifAddrStruct != NULL){
        if(strcmp(ifAddrStruct->ifa_name, interface.c_str()) == 0){
            if (ifAddrStruct->ifa_addr->sa_family == AF_INET){
                // check it is IP4
                // is a valid IP4 Address
                tmpAddrPtr = &((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr;
                char addressBuffer[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
                ip = addressBuffer;
                found = true;
                return found;
                //printf("%s IPV4 Address %s\n", ifAddrStruct->ifa_name, addressBuffer);
            }
            //else if (ifAddrStruct->ifa_addr->sa_family == AF_INET6){
            //    // check it is IP6
            //    // is a valid IP6 Address
            //    tmpAddrPtr = &((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr;
            //    char addressBuffer[INET6_ADDRSTRLEN];
            //    inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            //    ip = addressBuffer;
            //    //printf("%s IPV6 Address %s\n", ifAddrStruct->ifa_name, addressBuffer);
            //}
        }
        ifAddrStruct = ifAddrStruct->ifa_next;
    }
    //cout << defalutInterface << endl;
    cout << "Get Address: Interface not found.\n";
    return found;
}

void Server::sendAddrToClient(const string& interface)
{
    int serverFD;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    fd_set readFD;
    struct timeval timeout;
    string ip;
    uint8_t *buffer = new uint8_t[BUFFER_SIZE];

    getAddress(interface, ip);
    socklen_t socketLen = sizeof(struct sockaddr_in);
    int recvLen = 0;

    if((serverFD = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
        cerr << "UDP Server: Socket create failed\n";
        exit(1);
    }
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(UDP_PORT);
    serverAddr.sin_addr.s_addr = htons(INADDR_ANY);
    memset(&serverAddr.sin_zero, 0, sizeof(serverAddr));

    if(bind(serverFD, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr)) == -1){
        cerr << "UDP Server: Bind failed.\n";
        cerr << "UDP Server: Error code:" << errno << endl;
        exit(1);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    cout << "Server(UDP) is running, Port: " << UDP_PORT << endl;
    while(UDPServerFlag){
        FD_ZERO(&readFD);
        FD_SET(serverFD, &readFD);
        timeout.tv_sec = 1;
        switch((select(serverFD + 1, &readFD, NULL, NULL, &timeout))){
        case -1:
            cerr << "UDP Server: Select error.\n";
            goto error;
            //break;
        case 0:
            cerr << "UDP Server: Time out.\n";
            break;
        default:

            if (FD_ISSET(serverFD ,&readFD)) {
                recvLen = recvfrom(serverFD, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&clientAddr, &socketLen);
                if(recvLen > 0)
                    cout << "Received client request, IP: " << (char *)inet_ntoa(clientAddr.sin_addr) << "\n";
                memcpy(buffer, ip.c_str(), ip.length() + 1);
                recvLen = sendto(serverFD, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&clientAddr, socketLen);
            }

        }
    }

    error: delete []buffer;
           FD_CLR(serverFD, &readFD);
}

void Server::startUDPServer()
{
    UDPServerFlag = true;
    UDPThread = new thread([=]{ sendAddrToClient(defInterface); });
}

void Server::stopUDPServer()
{

    if(UDPThread != nullptr){
        cerr << "Stop UDP Server.\n";
        UDPServerFlag = false;
    }
    while(UDPThread == nullptr);

}

void Server::startTCPServer()
{
    TCPServerFlag = true;

}

void Server::stopTCPServer()
{
    if(TCPThread != nullptr){
        cerr << "Stop TCP Server.\n";
        TCPServerFlag = false;
    }

}

Server::~Server()
{
    stopUDPServer();
    stopTCPServer();
}

//int main(int argc, char *argv[])
//{
//    if(argc > 1)
//        defalutInterface = argv[1];
//    int serverFD, clientFD;
//    struct sockaddr_in serverAddr;
//    struct sockaddr_in clientAddr;
//    socklen_t socketLen = sizeof(struct sockaddr_in);
//    thread clientASS(sendToClient);

//    if((serverFD = socket(AF_INET, SOCK_STREAM, 0)) == -1){
//        cerr << "Socket create failed\n";
//        exit(1);
//    }

//    serverAddr.sin_family = AF_INET;
//    serverAddr.sin_port = htons(TCP_PORT);
//    serverAddr.sin_addr.s_addr = INADDR_ANY;
//    memset(&serverAddr.sin_zero, 0, sizeof(serverAddr));

//    if(bind(serverFD, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr)) == -1){
//        cerr << "Bind failed.\n";
//        exit(1);
//    }

//    if(listen(serverFD, _CONNECT_LIMIT) == -1){
//        cerr << "Listen error.\n";
//        exit(1);
//    }
//    cout << "Server(TCP) is running, Port: " << TCP_PORT << endl;
//    while(1){

//        if((clientFD = accept(serverFD, (struct sockaddr *)&clientAddr, &socketLen)) == -1){
//            cerr << "Accept error.\n";
//            continue;
//        }

//        cout << "New client:" << (char *)inet_ntoa(clientAddr.sin_addr) << "\n";

//        if(!fork()){
//            uint8_t *buffer = new uint8_t[_BUFFER_SIZE];
//            int32_t recvLen, packageLen;
//            while(1){
//                if((recvLen = read(clientFD, buffer, _BUFFER_SIZE)) < 0){
//                    cerr << "Read error.\n";
//                }
//                packageLen = ((PackageHead *)buffer)->length;

//                cout << recvLen << "\n";
//                cout << packageLen << "\n";
//                if(recvLen - packageLen == _HEAD_LENGTH){
//                    cout << "Received header package.\n";
//                    if(((PackageHead *)buffer)->magic != _MAGIC_NUM){
//                        cerr << "Broken header package, drop.\n";
//                        continue;
//                    }
//                    if(((PackageHead *)buffer)->command == _CMD_DISCONNECT){
//                        cout << "Client request disconnect.\n";
//                        break;
//                    }
//                    cout << "Expect data length: " << packageLen << "\n";
//                    cout << "Client say:" << (char *)buffer + _HEAD_LENGTH << "\n";
//                }
//                else if(recvLen == 0){
//                    cout << "Client disconnect.\n";
//                    break;
//                }
//                else{
//                    cerr << "Unkonw data, drop.\n";
//                    break;
//                }
//            }
//            delete []buffer;
//            close(clientFD);
//            clientASS.detach();
//            cout << "Server(UDP) close connect.\n";
//            cout << "Server(TCP) close connect.\n";
//        }
//    }
//}
