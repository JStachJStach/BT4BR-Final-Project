#pragma once
#include "Actor.h"
#include "global_enums.h"

class Rabbit final : public Actor
{
public:
    Rabbit() : Actor(
        TileState::Rabbit,
         rabbitStartingEnergy,
         rabbitMaxEnergy,
         rabbitReproductionEnergy,
         rabbitReproductionCost,
         static_cast<int>(ActorMovements::Rabbit),
         GRAY)
    {
        _currentEnergy = rabbitStartingEnergy;
        _sightValue = rabbitSightValue;
        _movementEnergyCost = rabbitEnergyPerTick;
        _energyPerMeal = rabbitMaxEnergy;
    }

    void act(Position pos, Grid& _grid, std::unique_ptr<Actor> actor) override;
    // 1. Check if Enough energy to move, if not die()
    // 2. Choose next position to move to
    // 3. Check if position is valid
    // if position is invalid GOTO 2.
    // 4. Queue Move to position if valid
    // 5. Try to eat grass if energy below threshold
    void tryToEat(Position pos, Grid& _grid) override;
    Position chooseNextPosition(const Position pos, const Grid& _grid) const;

    void reproduce(Position pos, Grid& _grid);
    void die() override;
private:
    int _currentEnergy;
    int _sightValue;
    int _movementEnergyCost;
    int _energyPerMeal;
    Position _nextPosition{};
};


