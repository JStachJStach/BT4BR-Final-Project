#pragma once
#include "Actor.h"


class Rabbit : public Actor
{
    public:
    Rabbit() : Actor(GRAY) {}
    void act(Position pos, Grid& _grid) override;
    TileState type() const noexcept override;

};


