#include "../headers/Fox.h"

void Fox::act(Position pos, Grid &_grid)
{
    Actor::act(pos, _grid);
}

TileState Fox::type() const noexcept
{
    return TileState::Fox;
}
