#pragma once
#include "Tile.h"


class Grass : public Tile
{
    public:
    explicit Grass() : Tile(GREEN) {}
    void act(Position pos, Grid& _grid) override;
    TileState type() const noexcept override;
};
