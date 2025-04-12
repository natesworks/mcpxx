#include "utilities.h"
#include "../core/server.h"

void Utilities::dumpPacket(State state, uint32_t packetID, std::vector<uint8_t> data)
{
#ifdef DUMPPACKETS
	std::string directory = "dumpedpackets/" + std::to_string(state);
	std::filesystem::create_directories(directory); // Create directories if they don't exist

	std::ofstream stream(directory + "/" + std::to_string(packetID) + ".bin", std::ios::binary);
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