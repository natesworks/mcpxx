#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <cstring>

#include "../data/blockposition.h"
#include "logger.h"

#define SEGMENTBITS 0x7F
#define CONTINUEBIT 0x80

class Bytestream
{
public:
	Bytestream(const std::vector<uint8_t> &buffer);

	/* Read functions */
    bool readBool();
	int8_t readByte();
    uint8_t readUnsignedByte();
    int16_t readShort();
    uint16_t readUnsignedShort();
    int32_t readInt();
    int64_t readLong();
    float readFloat();
    double readDouble();
    int32_t readVInt();
    int64_t readVLong();
    std::string readString();
    BlockPosition readBlockPosition();
    int8_t readAngle();

private:
	std::vector<uint8_t> buffer;
    uint32_t offset;
    union FloatUnion
    {
        int value;
        float fvalue;
    };
};