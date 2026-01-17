//
// Created by kiki on 15.01.2026.
//

#include "../headers/Actor.h"

void Actor::act(Position pos, Grid &_grid)
{
}

TileState Actor::type() const noexcept
{
    return TileState::None;
}

Color Actor::getColor() const
{
    return color_;
}
