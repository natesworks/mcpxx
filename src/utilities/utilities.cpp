#include "utilities.h"
#include "../core/server.h"

void Utilities::dumpPacket(Type type, State state, uint32_t packetID, std::vector<uint8_t> data)
{
#ifdef DUMPPACKETS
	std::string directory = "dumpedpackets/" + typeToString(type) + "/" + std::to_string(state);
	std::filesystem::create_directories(directory); // Create directories if they don't exist

	std::ofstream stream(directory + "/" + toHex(packetID) + ".bin", std::ios::binary);
	for (uint8_t byte : data)
	{
		stream << byte;
	}
#endif
}

std::string Utilities::toHex(uint32_t num)
{
	std::stringstream stream;
	stream << std::hex << num;
	std::string result(stream.str());
	return "0x" + result;
}

std::string Utilities::typeToString(Type type)
{
	if (type == ServerType)
		return "Server";
	return "Client";
}