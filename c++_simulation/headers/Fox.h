#pragma once
#include "Actor.h"


class Fox : public Actor
{
public:
    Fox() : Actor(TileState::Fox,
         rabbitStartingEnergy,
         rabbitMaxEnergy,
         rabbitReproductionEnergy,
         rabbitReproductionCost,
         static_cast<int>(ActorMovements::Fox),
         ORANGE) {}
    void act(Position pos, Grid& _grid, std::unique_ptr<Actor> actor) override;
private:

};

