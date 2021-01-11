#ifndef CHANCE_HPP
#define CHANCE_HPP
#include "util/Random.hpp"
bool getChanceOf(const int percent)
{
    return Random<int>(100) <= percent;
}
#endif