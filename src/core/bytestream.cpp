#include "bytestream.h"

Bytestream::Bytestream(const std::vector<uint8_t> &buffer, uint32_t offset)
	: buffer(buffer)
	, offset(offset)
{
}

bool Bytestream::readBool()
{
	bool value = buffer[offset];
	offset++;
	return value;
}

int8_t Bytestream::readByte()
{
	int8_t value = buffer[offset];
	offset++;
	return value;
}

uint8_t Bytestream::readUnsignedByte()
{
	uint8_t value = buffer[offset];
	offset++;
	return value;
}

int16_t Bytestream::readShort()
{
	int16_t value = (buffer[offset] << 8) | buffer[offset + 1];
	offset += 2;
	return value;
}

uint16_t Bytestream::readUnsignedShort()
{
	uint16_t value = (buffer[offset] << 8) | buffer[offset + 1];
	offset += 2;
	return value;
}

int32_t Bytestream::readInt()
{
	int32_t value = (buffer[offset] << 24) | (buffer[offset + 1] << 16) | (buffer[offset + 2] << 8) | buffer[offset + 3];
	offset += 4;
	return value;
}

int64_t Bytestream::readLong()
{
	int64_t value = ((int64_t)buffer[offset] << 56) | ((int64_t)buffer[offset + 1] << 48) | ((int64_t)buffer[offset + 2] << 40) | ((int64_t)buffer[offset + 3] << 32) | ((int64_t)buffer[offset + 4] << 24) | ((int64_t)buffer[offset + 5] << 16) | ((int64_t)buffer[offset + 6] << 8) | (int64_t)buffer[offset + 7];
	offset += 8;
	return value;
}

float Bytestream::readFloat()
{
	int32_t value = readInt();
	float floatValue;
	std::memcpy(&floatValue, &value, 4);
	return floatValue;
}

double Bytestream::readDouble()
{
	int64_t value = readLong();
	double doubleValue;
	std::memcpy(&doubleValue, &value, 8);
	return doubleValue;
}

/* https://minecraft.wiki/w/Java_Edition_protocol#VarInt_and_VarLong */

int32_t Bytestream::readVInt()
{
	int value = 0;
	int position = 0;
	int8_t currentByte;

	while (true)
	{
		currentByte = readByte();
		value |= (currentByte & SEGMENTBITS) << position;

		if ((currentByte & CONTINUEBIT) == 0)
			break;

		position += 7;

		if (position >= 32)
			Logger::error("VInt is too big");
	}

	return value;
}

int64_t Bytestream::readVLong()
{
	int64_t value = 0;
	int position = 0;
	int8_t currentByte;

	while (true)
	{
		currentByte = readByte();
		value |= (currentByte & SEGMENTBITS) << position;

		if ((currentByte & CONTINUEBIT) == 0)
			break;

		position += 7;

		if (position >= 64)
			Logger::error("VLong is too big");
	}

	return value;
}

std::string Bytestream::readString()
{
	int length = readVInt();
	std::string value(buffer.begin() + offset, buffer.begin() + offset + length);
	offset += length;
	return value;
}

BlockPosition Bytestream::readBlockPosition()
{
	int64_t value = readLong();
	int x = (value >> 38) & 0x3FFFFFF;
	int y = (value >> 26) & 0xFFF;
	int z = value & 0x3FFFFFF;
	return BlockPosition(x, y, z);
}

int8_t Bytestream::readAngle()
{
	int8_t value = readByte();
	return value;
}

void Bytestream::writeBool(bool value)
{
	buffer.push_back(value);
}

void Bytestream::writeByte(int8_t value)
{
	buffer.push_back(value);
}

void Bytestream::writeUnsignedByte(uint8_t value)
{
	buffer.push_back(value);
}

void Bytestream::writeShort(int16_t value)
{
	buffer.push_back(value >> 8);
	buffer.push_back(value & 0xFF);
}

void Bytestream::writeUnsignedShort(uint16_t value)
{
	buffer.push_back(value >> 8);
	buffer.push_back(value & 0xFF);
}

void Bytestream::writeInt(int32_t value)
{
	buffer.push_back(value >> 24);
	buffer.push_back((value >> 16) & 0xFF);
	buffer.push_back((value >> 8) & 0xFF);
	buffer.push_back(value & 0xFF);
}

void Bytestream::writeLong(int64_t value)
{
	buffer.push_back(value >> 56);
	buffer.push_back((value >> 48) & 0xFF);
	buffer.push_back((value >> 40) & 0xFF);
	buffer.push_back((value >> 32) & 0xFF);
	buffer.push_back((value >> 24) & 0xFF);
	buffer.push_back((value >> 16) & 0xFF);
	buffer.push_back((value >> 8) & 0xFF);
	buffer.push_back(value & 0xFF);
}

void Bytestream::writeFloat(float value)
{
	int32_t intValue;
	std::memcpy(&intValue, &value, 4);
	writeInt(intValue);
}

void Bytestream::writeDouble(double value)
{
	int64_t intValue;
	std::memcpy(&intValue, &value, 8);
	writeLong(intValue);
}

void Bytestream::writeVInt(int32_t value)
{
	while (true)
	{
		if ((value & ~SEGMENTBITS) == 0)
		{
			writeByte(value);
			return;
		}
		else
		{
			writeByte((value & SEGMENTBITS) | CONTINUEBIT);
			value >>= 7;
		}
	}
}

void Bytestream::writeVLong(int64_t value)
{
	while (true)
	{
		if ((value & ~SEGMENTBITS) == 0)
		{
			writeByte(value);
			return;
		}
		else
		{
			writeByte((value & SEGMENTBITS) | CONTINUEBIT);
			value >>= 7;
		}
	}
}

void Bytestream::writeString(const std::string &value)
{
	writeVInt(value.length());
	buffer.insert(buffer.end(), value.begin(), value.end());
}

void Bytestream::writeBlockPosition(const BlockPosition &value)
{
	int64_t packedValue = ((int64_t)value.x << 38) | ((int64_t)value.y << 26) | (int64_t)value.z;
	writeLong(packedValue);
}

void Bytestream::writeAngle(int8_t value)
{
	writeByte(value);
}

uint32_t Bytestream::getOffset()
{
	return offset;
}

std::vector<uint8_t> Bytestream::getBuffer()
{
	return buffer;
}

void Bytestream::skipHeader()
{
	readVInt();
	readVInt();
}

void Bytestream::writePacketHeader(uint16_t packetID)
{
	Bytestream header;
	header.writeVInt(buffer.size());
	header.writeVInt(packetID);
	buffer.insert(buffer.begin(), header.getBuffer().begin(), header.getBuffer().end());
}