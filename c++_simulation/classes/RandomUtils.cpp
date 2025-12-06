#include "../headers/RandomUtils.h"
inline std::random_device dev;
const long long SEED = dev(); //Advance the engine and use it as a variable for reproducibility purposes
std::mt19937 rng(SEED);

int RandomUtils::get_random_cell()
{
    std::uniform_int_distribution<std::mt19937::result_type> distOnGrid(0, gridSize - 1);
    return distOnGrid(rng);
}

void RandomUtils::save_seed()
{
    std::fstream seedFile("../data/seed.txt", std::fstream::out);
    if (seedFile.is_open())
    {
        seedFile << "Seed used:" << SEED;
    }
    seedFile.close();
}