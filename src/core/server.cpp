#include "server.h"

void Server::handleClient(CallingInstance &ci)
{
    try
    {
        time_t timeout = time(nullptr);

        sockaddr_in clientAddr;
        socklen_t addrLen = sizeof(clientAddr);
        if (getpeername(ci.socket, (sockaddr *)&clientAddr, &addrLen) == -1)
        {
            Logger::error("Failed to get client IP");
            return;
        }

        char clientIp[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clientAddr.sin_addr, clientIp, INET_ADDRSTRLEN);

        while (true)
        {
            uint8_t temp[5];
            int head = recv(ci.socket, temp, 5, 0);
            if (head < 5)
            {
                Logger::error("Failed to read packet header");
                break;
            }

            Bytestream tempStream(std::vector<uint8_t>(temp, temp + head));
            int32_t packetLength = tempStream.readVInt();

            ci.data.resize(packetLength);
            int bytesRead = 0;
            while (bytesRead < packetLength)
            {
                int part = recv(ci.socket, ci.data.data() + bytesRead, packetLength - bytesRead, 0);
                if (part <= 0)
                {
                    break;
                }
                bytesRead += part;
            }

            ci.data.insert(ci.data.begin(), temp, temp + head);
            Bytestream stream(ci.data);
            stream.readVInt();
            ci.packetID = stream.readVInt();

            if (time(nullptr) - timeout > 30)
            {
                Logger::log("Client disconnected due to inactivity: " + std::string(clientIp));
                close(ci.socket);
                return;
            }

            Messaging::handlePacket(ci);
            timeout = time(nullptr);
        }
    }
    catch (...)
    {
        close(ci.socket);
    }
}

int Server::createSocket()
{
#ifdef _WIN32
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return -1;
	}
#endif

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1)
	{
		return -1;
	}

	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
	{
		close(serverSocket);
		return -2;
	}

	return serverSocket;
}

void Server::listenForConnections()
{
	if (listen(serverSocket, 10) == -1)
	{
		Logger::error("Failed to listen on socket");
		close(serverSocket);
		return;
	}

	Logger::log("Listening for connections...");

	while (true)
	{
		CallingInstance ci;
		sockaddr_in clientAddress;
		socklen_t clientLen = sizeof(clientAddress);
		ci.socket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientLen);

		if (ci.socket >= 0)
		{
			Logger::log("Client connected");
			std::thread(handleClient, std::ref(ci)).detach();
		}
	}
}
