#pragma once
#include "Actor.h"


class Fox : public Actor
{
public:
    Fox() : Actor(ORANGE) {}
    void act(Position pos, Grid& _grid) override;
    TileState type() const noexcept override;
private:

};

