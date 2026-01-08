#define _CRT_SECURE_NO_WARNINGS
#include "../headers/RandomUtils.h"
// Global variables
inline std::random_device dev;
const long long SEED = dev(); //Advance the engine and use it as a variable for reproducibility purposes
std::mt19937 rng(SEED);

/**
 * Method for getting random integer in a range defined by user
 * @param lowerBound Lower bound of number to generate
 * @param upperBound Upper bound of number to generate
 * @return Random integer in defined range
 */
int RandomUtils::get_random_num(const int& lowerBound, const int& upperBound)
{
    std::uniform_int_distribution<> randomResult(lowerBound, upperBound);
    return randomResult(rng);
}

/**
 * Method for getting random floating point number in a range defined by user
 * @param lowerBound Lower bound of number to generate
 * @param upperBound Upper bound of number to generate
 * @return Random floating point number in defined range
 */
float RandomUtils::get_random_float(const float &lowerBound, const float &upperBound)
{
    std::uniform_real_distribution<float> randomResult(lowerBound, upperBound);
    return randomResult(rng);
}

/**
 * Method for saving seed used for random number generation
 */
void RandomUtils::save_seed()
{
    // Open file for saving seed
    const std::string path = "../data/settings_used.txt";
    std::ofstream seedFile(path);
    const time_t cur_time = time(nullptr);
    const tm *local_time = localtime(&cur_time);
    // Check if file has opened correctly
    if (seedFile.is_open())
    {
        seedFile << "Ecosystem Simulation v0.1.0" << std::endl;
        seedFile << "Ran at: " << asctime(local_time);
        seedFile << "Seed used: " << SEED << std::endl << std::endl;
        seedFile.close();
    }
    else
    {
       throw std::runtime_error("Could not open seed file at " + path);
    }

}

/**
 * Method to get adjacent positions
 * @param currentPosition Tile position
 * @return Array of positions adjacent to currentPosition
 */
std::array<std::array<int, 2>, 8> RandomUtils::positionsAdjacent(const std::array<int,2> currentPosition)
{
    // C++ is smart enough to not need explicit std::array<std::array<int, 2>, 8> call here so auto is used
    auto toReturn = std::array{
        std::array{-1, -1},
        std::array{-1, 0},
        std::array{-1, 1},
        std::array{0, -1},
        std::array{0, 1},
        std::array{1, -1},
        std::array{1, 0},
        std::array{1, 1}
    };
    for (auto& pos : toReturn)
    {
        pos[0] += currentPosition[0];
        pos[1] += currentPosition[1];
    }
    std::ranges::shuffle(toReturn,rng);
    return toReturn;
}

/**
 * Method that adds a random tile depending on tile state
 * @param tileMap array of all currently active tiles
 * @param state state of tile that controls what role and color it has
 */
void RandomUtils::get_random_tile(std::map<std::array<int, 2>, Tile>& tileMap, const TileState & state)
{
    switch (state)
    {
        case TileState::Grass :
        {
            const Tile *tile = new Tile("Grass", GREEN);
            tileMap[std::array<int, 2>{_get_random_cell(), _get_random_cell()}] = *tile;
            break;
        }
        case TileState::Rabbit :
        {
            const Tile *tile = new Tile("Rabbit", GRAY);
            tileMap[std::array<int, 2>{_get_random_cell(), _get_random_cell()}] = *tile;
            break;
        }
        case TileState::Fox :
        {
            const Tile *tile = new Tile("Fox", ORANGE);
            tileMap[std::array<int, 2>{_get_random_cell(), _get_random_cell()}] = *tile;
            break;
        }
        default: ;
    }
}

/**
 * Method that gets random coordinates of cells
 * @return Random cell coordinates
 */
int RandomUtils::_get_random_cell()
{
    std::uniform_int_distribution<std::mt19937::result_type> distanceOnGrid(0, gridSize-1);
    return distanceOnGrid(rng);
}

