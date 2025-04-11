#pragma once

#include <iostream>
#ifdef _WIN32
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
/* Aliases to not add a billion ifdefs */
#define close closesocket
#define usleep(x) Sleep((x) / 1000)
#pragma comment(lib, "ws2_32.lib")
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif
#include <ctime>
#include <thread>
#include <vector>
#include "../data/callinginstance.h"
#include "logger.h"
#include "messaging.h"
#include "bytestream.h"

class Server
{
public:
    const int port = 25565;
    int serverSocket;
    static void handleClient(CallingInstance &ci);
    int createSocket();
    void listenForConnections();
};