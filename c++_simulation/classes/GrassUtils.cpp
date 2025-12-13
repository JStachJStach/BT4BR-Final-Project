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
        for (int i = 0; i < grassPositions.size(); ++i)
        {
            Tile *tile = new Tile("Grass", GREEN);
            tile->set_state(TileState::Grass);
            const int newXPosition = RandomUtils::get_random_num(-1,1);
            const int newYPosition = RandomUtils::get_random_num(-1,1);
            std::array<int, 2> newGrassPosition = {grassPositions[i][0] + newXPosition, grassPositions[i][1] + newYPosition};
            tileMap[newGrassPosition] = *tile;
        }
    }
}
