#pragma once

#include <functional>
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
#include "../data/callinginstance.h"
#include "bytestream.h"
#include "logger.h"
#include "messaging.h"
#include "../utilities/utilities.h"
#include <ctime>
#include <map>
#include <thread>
#include <vector>

/* https://minecraft.wiki/w/Minecraft_Wiki:Projects/wiki.vg_merge/Protocol_version_numbers */
#define PROTOCOLVERSION 770 // 1.21.5
#define SNAPSHOT 0x40000000
//#define SINGLETHREADED
#define DUMPPACKETS
#define DEBUG // comment out to remove debug logs

class Server
{
public:
	const int port = 25565;
	int serverSocket;
	void handleClient(CallingInstance ci);
	int createSocket();
	void listenForConnections();
	void setHandler(State state, uint32_t packetID, std::function<void(CallingInstance &)> handler);
	uint32_t readPacketLength(CallingInstance &ci);

private:
	std::map<State, std::map<uint32_t, std::function<void(CallingInstance &)>>> handlers;
	void callHandler(CallingInstance &ci);
};