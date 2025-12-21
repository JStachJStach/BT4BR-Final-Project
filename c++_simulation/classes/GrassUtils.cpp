//
// Created by kiki on 12.12.2025.
//

#include "../headers/GrassUtils.h"

void GrassUtils::grow(std::map<std::array<int, 2>, Tile> &tileMap, const std::vector<std::array<int, 2>> &grassPositions)
{
    if (grassPositions.empty())
    {
        std::cerr << "No grass left to grow!" << std::endl;
    }
    if (grassPositions.size() < grassMaxAmount)
    {
        for (auto grassPosition : grassPositions)
        {
            const int newXPosition = RandomUtils::get_random_num(-1,1);
            const int newYPosition = RandomUtils::get_random_num(-1,1);
            std::array<int, 2> newGrassPosition = {grassPosition[0] + newXPosition, grassPosition[1] + newYPosition};
            if (!tileMap.contains(newGrassPosition))
                tileMap[newGrassPosition] = *(new Tile("Grass", GREEN));
        }
    }
}
