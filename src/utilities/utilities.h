#pragma once

#include <fstream>
#include <vector>
#include <cstdint>
#include <filesystem>
#include <string>
#include <iomanip>

#include "../data/state.h"
#include "../data/type.h"

class Utilities
{
public:
    static void dumpPacket(Type type, State state, uint32_t packetID, std::vector<uint8_t> data);
    static std::string toHex(uint32_t num);
    static std::string typeToString(Type type);
};