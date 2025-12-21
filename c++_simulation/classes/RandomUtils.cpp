#include "../headers/RandomUtils.h"
inline std::random_device dev;
const long long SEED = dev(); //Advance the engine and use it as a variable for reproducibility purposes
std::mt19937 rng(SEED);

int RandomUtils::get_random_num(const int& lowerBound, const int& upperBound)
{
    std::uniform_int_distribution<> randomResult(lowerBound, upperBound);
    return randomResult(rng);
}

void RandomUtils::save_seed()
{
    std::fstream seedFile("../data/Raw_Output.txt", std::fstream::out);
    if (seedFile.is_open())
    {
        seedFile << "Ecosystem Simulation v0.0.1" << std::endl;
        seedFile << "Seed used: " << SEED << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file" << std::endl;
    }
    seedFile.close();
}

/**
 * List of adjacent positions
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
 * Function that adds a random tile depending on tile state
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

int RandomUtils::_get_random_cell()
{
    std::uniform_int_distribution<std::mt19937::result_type> distanceOnGrid(0, gridSize-1);
    return distanceOnGrid(rng);
}

