#include "../headers/GrassUtils.h"

/**
 * Method to handle grass growing
 * @param tileMap Current map state
 * @param grassPositions Vector of grass positions
 */
void GrassUtils::grow(std::map<std::array<int, 2>, Tile>& tileMap, const std::vector<std::array<int, 2>>& grassPositions)
{
    // Iterate over grass positons
    for (auto grassPosition : grassPositions)
    {
        // Roll a random real number from 0 to 1 for a chance for grass to grow 
        if (grassGrowChance >= RandomUtils::get_random_float(0, 1))
        {
            if (grassGrowChance >= RandomUtils::get_random_float(0, 1))
            {
                const int newXPosition = RandomUtils::get_random_num(0, gridSize - 1);
                const int newYPosition = RandomUtils::get_random_num(0, gridSize - 1);
                std::array newGrassPosition = { newXPosition, newYPosition };
                if (!tileMap.contains(newGrassPosition) and newGrassPosition[0] > -1 and newGrassPosition[1] > -1 and newGrassPosition[0] < gridSize and newGrassPosition[1] < gridSize)
                    tileMap[newGrassPosition] = *(new Tile("Grass", GREEN));
            }
            // Get random adjacent Tile
            const int newXPosition = RandomUtils::get_random_num(-1, 1);
            const int newYPosition = RandomUtils::get_random_num(-1, 1);
            std::array newGrassPosition = { grassPosition[0] + newXPosition, grassPosition[1] + newYPosition };
            // If the new grass Tile doesn't exist yet, create it
            if (!tileMap.contains(newGrassPosition) and newGrassPosition[0] > -1 and newGrassPosition[1] > -1 and newGrassPosition[0] < gridSize and newGrassPosition[1] < gridSize)
                tileMap[newGrassPosition] = *(new Tile("Grass", GREEN));
        }
    }
}
