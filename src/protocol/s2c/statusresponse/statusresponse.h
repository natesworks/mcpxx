#pragma once

#include <string>
#include <map>
#include <cstdint>

#include "../../../data/packet.h"
#include "../../../utilities/utilities.h"

class StatusResponse : Packet
{
public:
    StatusResponse(CallingInstance &ci);
	~StatusResponse() override;
	std::string version;
	uint32_t protocolVersion;
	int32_t onlinePlayers;
	int32_t maxPlayers;
	std::vector<std::map<std::string, std::string>> players;
	std::string description;
	std::string favicon; // TODO utility to read image and convert to base64 and return data:image/<type>;base64,<data>
	bool enforcesSecureChat;

    void read() override;
	void write() override;
	uint16_t getPacketID() override;

private:
    CallingInstance &ci;
};