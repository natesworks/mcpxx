#pragma once

#include <cstdint>

struct BlockPosition
{
    int32_t x;
    int32_t y;
    int32_t z;

    BlockPosition(int32_t x, int32_t y, int32_t z) : x(x), y(y), z(z) {}
};