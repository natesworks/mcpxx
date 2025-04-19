#include "server.h"
#include "logger.h"

uint32_t Server::readVInt(CallingInstance &ci)
{
	uint32_t value = 0;
	int position = 0;

	for (size_t offset = 0; offset < ci.data.size(); ++offset)
	{
		uint8_t byte = ci.data[offset];
		value |= (byte & SEGMENTBITS) << position;

		if ((byte & CONTINUEBIT) == 0)
		{
			ci.packetLength = value;
			return offset + 1;
		}

		position += 7;
		if (position >= 32)
			throw std::runtime_error("VInt too large");
	}

	throw std::runtime_error("Error reading VInt");
}

void Server::handleClient(CallingInstance ci)
{
	try
	{
		sockaddr_in clientAddr;
		socklen_t addrLen = sizeof(clientAddr);
		if (getpeername(ci.socket, (sockaddr *)&clientAddr, &addrLen) == -1)
			throw std::runtime_error("Failed to get client IP");

		char clientIp[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientAddr.sin_addr, clientIp, INET_ADDRSTRLEN);
		time_t timeout = time(nullptr);

		while (true)
		{
			uint8_t header[10];
			int headerRead = recv(ci.socket, header, sizeof(header), 0);
			if (headerRead <= 0)
				break;

			ci.data.assign(header, header + headerRead);
			uint32_t packetLengthSize = readVInt(ci);

			int totalSize = ci.packetLength + packetLengthSize;
			ci.data.resize(totalSize);

			int bytesRead = headerRead;
			while (bytesRead < totalSize)
			{
				int part = recv(ci.socket, ci.data.data() + bytesRead, totalSize - bytesRead, 0);
				if (part < 0)
					throw std::runtime_error("Failed to read full packet");
				bytesRead += part;
			}

			ci.nextState = ci.state;
			callHandler(ci, Messaging::handlePacket(ci));
			ci.state = ci.nextState;

			if (time(nullptr) - timeout > 30)
			{
				Logger::log("Client disconnected due to timeout: " + std::string(clientIp));
				break;
			}

			timeout = time(nullptr);
		}
	}
	catch (const std::exception &e)
	{
		Logger::debug("Client disconnected: " + std::string(typeid(e).name()) + ": " + std::string(e.what()));
	}
	catch (...)
	{
		Logger::debug("Client disconnected with unknown error");
	}

	close(ci.socket);
}

int Server::createSocket()
{
#ifdef _WIN32
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return -1;
#endif

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1)
		return -1;

	int opt = 1;
	setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));

	sockaddr_in serverAddress {};
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	if (bind(serverSocket, (sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
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
		CallingInstance ci(ServerType);
		sockaddr_in clientAddress {};
		socklen_t clientLen = sizeof(clientAddress);
		ci.socket = accept(serverSocket, (sockaddr *)&clientAddress, &clientLen);

		if (ci.socket >= 0)
		{
			Logger::log("Client connected");
			std::thread(&Server::handleClient, this, ci).detach();
		}
	}
}

void Server::setHandler(State state, uint16_t packetID, std::function<void(CallingInstance &ci, std::unique_ptr<Packet>)> handler)
{
	handlers[state][packetID] = handler;
}

void Server::callHandler(CallingInstance &ci, std::unique_ptr<Packet> packet)
{
	auto stateIt = handlers.find(ci.state);
	if (stateIt != handlers.end())
	{
		auto &packetMap = stateIt->second;
		auto handlerIt = packetMap.find(packet->getPacketID());
		if (handlerIt != packetMap.end())
			handlerIt->second(ci, std::move(packet));
	}
}