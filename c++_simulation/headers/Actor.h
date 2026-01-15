#pragma once
#include "Tile.h"

class Actor : public Tile
{
    public:
    explicit Actor(const Color color) : Tile(color) {}
    void act(Position pos, Grid& _grid) override;
    TileState type() const noexcept override;

private:
};

