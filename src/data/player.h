#pragma once

#include <string>
#include <vector>
#include <array>

#include "slotdata.h"

class Player
{
public:
    std::string uuid;
    std::string name;
    std::vector<SlotData> inventory;
    std::array<SlotData, 4> armor;
    SlotData offhand;
};