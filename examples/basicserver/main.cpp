#include <mcpxx/core/server.h>
#include <mcpxx/data/state.h>
#include <mcpxx/protocol/c2s/handshake/handshake.h>
#include <mcpxx/protocol/s2c/statusresponse/statusresponse.h>
#include <thread>

void test(CallingInstance &ci, std::unique_ptr<Packet> packet)
{
	auto handshakingPacket = std::unique_ptr<Handshake>(static_cast<Handshake *>(packet.release()));
	Logger::debug("Protocol version: " + std::to_string(handshakingPacket->protocolVersion));
	Logger::debug("Server address: " + handshakingPacket->serverAddress);
	Logger::debug("Port: " + std::to_string(handshakingPacket->port));
	Logger::debug("Next state: " + std::to_string(ci.nextState));
}

void statusResponse(CallingInstance &ci, std::unique_ptr<Packet> packet)
{
    StatusResponse response(ci);
    response.description = "Cool server!";
    response.maxPlayers = 1;
    response.enforcesSecureChat = false;
    response.onlinePlayers = 903;
    response.players = { { { "name", "Natesworks" }, { "id", "c8498618-1eb4-4640-b74c-71f707f7596c" } } };
    response.version = "mcpxx";
    response.protocolVersion = 770;
    response.write();
}

int main(void)
{
	Server server;
	server.createSocket();
	server.setHandler(Handshaking, 0x0, test);
    server.setHandler(Status, 0x0, statusResponse);
	server.listenForConnections();
}