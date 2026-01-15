#pragma once
#include <random>
#include <algorithm>
#include <ctime>
#include "settings.h"

#include "Grass.h"
#include "Fox.h"
#include "Rabbit.h"
#include "TileMap.h"
// Start Values
extern std::mt19937 rng;
class RandomUtils
{
public:
    static int get_random_num(const int& lowerBound, const int& upperBound);
    static float get_random_float(const float& lowerBound, const float& upperBound);
    static void save_seed();
    static  std::vector<Position> positionsAdjacent(Position, int = 1);
    static void get_random_tile(Grid& grid,const TileState& state);
private:
    static int _get_random_cell();
};

