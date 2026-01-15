#include "../headers/Tile.h"

void Tile::draw(const Position& currentPosition) const
{
    //tile color should be based on name and state
    DrawRectangle(currentPosition.x_pos * cellSize, currentPosition.y_pos * cellSize, cellSize, cellSize, color_);
}
