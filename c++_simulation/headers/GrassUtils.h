#pragma once
#include "Tile.h"
#include "RandomUtils.h"
#include "settings.h"

class GrassUtils : Tile
{
public:
    static void grow(std::map<std::array<int, 2>, Tile>& tileMap, const std::vector<std::array<int, 2>>& grassPositions);
};

