#pragma once
#include <random>
#include <algorithm>
#include "settings.h"
#include "Tile.h"
// Start Values
extern std::mt19937 rng;
class RandomUtils
{
public:
    static int get_random_num(const int& lowerBound, const int& upperBound);
    void save_seed();
    static std::array<std::array<int, 2>, 8> positionsAdjacent(const std::array<int, 2>);
    static void get_random_tile(std::map<std::array<int, 2>, Tile>& tileMap,const TileState& state);
private:
    static int _get_random_cell();
};

