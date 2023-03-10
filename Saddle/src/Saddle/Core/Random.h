#pragma once

#include <random>

namespace Saddle {

class Random {
public:
    static uint32_t RandInt();
    static uint32_t RandInt(uint32_t low, uint32_t high);
};

}