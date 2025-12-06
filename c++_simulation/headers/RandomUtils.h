#pragma once
#include <random>
#include "settings.h"
#include "fstream"
// Start Values
extern std::mt19937 rng;
class RandomUtils
{
public:
    static int get_random_cell();
    void save_seed();
};

