//
// Created by kiki on 15.01.2026.
//

#include "../headers/Actor.h"

#include "../headers/Grid.h"

void Actor::act(Position pos, Grid &_grid, std::unique_ptr<Actor> actor)
{
}

void Actor::tryToEat(Position pos, Grid &_grid)
{

}

TileState Actor::type() const noexcept
{
    return _type;
}

Color Actor::getColor() const
{
    return _color;
}

void Actor::die()
{
}

void Actor::move(const Position& pos_old, const Position& pos_new, Grid &_grid, std::unique_ptr<Actor> actor)
{
    if (_grid.inBounds(pos_new))
    {
        _grid.moveActor(pos_old, std::move(actor));
        _grid.appendMoveRequest(pos_old, pos_new, _type);
    }

    else
        _grid.moveActor(pos_old, std::move(actor));
}

TileState Actor::getType_() const
{
    return _type;
}

int Actor::getInitialEnergy_() const
{
    return _initialEnergy;
}

int Actor::getMaxEnergy_() const
{
    return _maxEnergy;
}

int Actor::getReproductionThreshold_() const
{
    return _reproductionThreshold;
}

int Actor::getReproductionCost_() const
{
    return _reproductionCost;
}

int Actor::getMovesPerTick_() const
{
    return _movesPerTick;
}

Color Actor::getColor_() const
{
    return _color;
}

void Actor::setAlive_(const bool & isAlive)
{
    _alive = isAlive;
}

void Actor::eat()
{

}
