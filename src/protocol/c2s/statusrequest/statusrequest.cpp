#include "statusrequest.h"

void StatusRequest::read()
{
    
}

void StatusRequest::write()
{
    ci.stream = Bytestream();
    ci.stream.writePacketHeader(getPacketID());
    send(ci.socket, ci.stream.getBuffer().data(), ci.stream.getBuffer().size(), 0);
}

uint16_t StatusRequest::getPacketID()
{
    return 0x0;
}