#pragma once

#include "callinginstance.h"

class Packet
{
public:
	Packet(CallingInstance &ci) : ci(ci) {}
	virtual ~Packet() = default;
	virtual void read() = 0;
	virtual void write() = 0;
	virtual uint16_t getPacketID() = 0;

private:
	CallingInstance &ci;
};