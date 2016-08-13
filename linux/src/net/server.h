#pragma once

#include <iostream>
#include <cstdlib>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <thread>
#include <arpa/inet.h>
#include <ifaddrs.h>

using namespace std;

class Server
{
public:
    Server()
    {
        UDPThread = nullptr;
        TCPThread = nullptr;
        UDPServerFlag = false;
        TCPServerFlag = false;

    }
    ~Server();
    void setInterface(const string interface = "eth0"){ defInterface = interface; }
    static bool getAddress(const string &interface, string &ip);
    void startUDPServer();
    void stopUDPServer();
    void startTCPServer();
    void stopTCPServer();
private:
    string defInterface;
    thread *UDPThread;
    thread *TCPThread;
    bool UDPServerFlag;
    bool TCPServerFlag;
    void sendAddrToClient(const std::string &interface);

};
