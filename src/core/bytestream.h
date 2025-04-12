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
    Bytestream() = default;

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

    /* Write functions */
    void writeBool(bool value);
	void writeByte(int8_t value);
    void writeUnsignedByte(uint8_t value);
    void writeShort(int16_t value);
    void writeUnsignedShort(uint16_t value);
    void writeInt(int32_t value);
    void writeLong(int64_t value);
    void writeFloat(float value);
    void writeDouble(double value);
    void writeVInt(int32_t value);
    void writeVLong(int64_t value);
    void writeString(const std::string& value);
    void writeBlockPosition(const BlockPosition& value);
    void writeAngle(int8_t angle);

private:
	std::vector<uint8_t> buffer;
    uint32_t offset;
    union FloatUnion
    {
        int value;
        float fvalue;
    };
};