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
    const std::string path = set_path("../data/settings_used.txt");
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
 * @param rangeOfSight Range of adjacent tiles
 * @return Array of positions adjacent to currentPosition
 */
 std::vector<Position> RandomUtils::positionsAdjacent(const Position currentPosition, const int rangeOfSight)
{

    std::vector<Position> positions;

    for (auto i = -rangeOfSight; i <= rangeOfSight; i++)
    {
        for (int j = -rangeOfSight;j <= rangeOfSight; j++)
        {
            if (i != 0 || j != 0)
                positions.push_back({i,j});
        }
    }
    for (auto& pos : positions)
    {
        pos.x_pos += currentPosition.x_pos;
        pos.y_pos += currentPosition.y_pos;
    }
    std::ranges::shuffle(positions,rng);
    return positions;
}

/**
 * Method that adds a random tile depending on tile state
 * @param grid array of all currently active tiles
 * @param state state of tile that controls what role and color it has
 */
void RandomUtils::get_random_tile(Grid& grid, const TileState & state)
{
    switch (state)
    {
        case TileState::Grass :
        {
            while (true)
            {
                const Position pos{_get_random_cell(), _get_random_cell()};

                try
                {
                    grid.get(pos)->seed(10);
                    grid.appendGrassPos(pos);
                    return;
                }
                catch (...)
                {
                    std::cerr << "Error while adding grass tile" << std::endl;
                }
            }
        }
        case TileState::Rabbit :
        {
            while (true)
            {
                const Position pos{_get_random_cell(), _get_random_cell()};

                try
                {
                    auto rabbit = std::make_unique<Rabbit>();
                    grid.addActor(pos, std::move(rabbit));
                    return;
                }
                catch (...)
                {
                    std::cerr << "Error while adding rabbit tile" << std::endl;
                }
            }
        }
        case TileState::Fox :
        {
            while (true)
            {
                const Position pos{_get_random_cell(), _get_random_cell()};

                try
                {
                    auto fox = std::make_unique<Fox>();
                    grid.addActor(pos, std::move(fox));
                    return;
                }
                catch (...)
                {
                    std::cerr << "Error while adding fox tile" << std::endl;
                }
            }
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

