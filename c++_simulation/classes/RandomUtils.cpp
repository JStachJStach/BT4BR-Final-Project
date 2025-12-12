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
            Tile *tile = new Tile("Grass", GREEN);
            tile->set_state(TileState::Grass);
            tileMap[std::array<int, 2>{_get_random_cell(), _get_random_cell()}] = *tile;
            break;
        }
        case TileState::Rabbit :
        {
            Tile *tile = new Tile("Rabbit", GRAY);
            tile->set_state(TileState::Rabbit);
            tileMap[std::array<int, 2>{_get_random_cell(), _get_random_cell()}] = *tile;
            break;
        }
        case TileState::Fox :
        {
            Tile *tile = new Tile("Fox", ORANGE);
            tile->set_state(TileState::Fox);
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

