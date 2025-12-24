#include "../headers/GrassUtils.h"

/**
 * Method to handle grass growing
 * @param tileMap Current map state
 * @param grassPositions Vector of grass positions
 */
void GrassUtils::grow(std::map<std::array<int, 2>, Tile> &tileMap, const std::vector<std::array<int, 2>> &grassPositions)
{
    // Check if there is any grass left that can propagate
    if (grassPositions.empty())
    {
        std::cerr << "No grass left to grow!" << std::endl;
    }

    // Check if there is space for the grass to grow
    if (grassPositions.size() < grassMaxAmount)
    {
        // Iterate over grass positons
        for (auto grassPosition : grassPositions)
        {
            // Roll a random real number from 0 to 1 for a chance for grass to grow (DEFAULT = 75%)
            if (grassGrowChance >= RandomUtils::get_random_float(0, 1))
            {
                // Get random adjacent Tile
                const int newXPosition = RandomUtils::get_random_num(-1,1);
                const int newYPosition = RandomUtils::get_random_num(-1,1);
                std::array newGrassPosition = {grassPosition[0] + newXPosition, grassPosition[1] + newYPosition};

                // If the new grass Tile doesn't exist yet, create it
                if (!tileMap.contains(newGrassPosition))
                    tileMap[newGrassPosition] = *(new Tile("Grass", GREEN));
            }
        }
    }
}
