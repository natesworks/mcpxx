#include "statusrequest.h"

void StatusRequest::read()
{
    
}

void StatusRequest::write()
{
    ci.stream.writePacketHeader(getPacketID());
}

uint16_t StatusRequest::getPacketID()
{
    return 0x0;
}