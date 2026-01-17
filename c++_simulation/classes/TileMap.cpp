#include "../headers/TileMap.h"


TileMap::TileMap() : _grid(screenWidth, screenHeight)
{
    // Set loop bounds
    constexpr auto TileMin = TileState::Grass;
    constexpr auto TileMax = TileState::Fox;
    // Iterate over the enum class and create tiles based on settings
    for (auto i = static_cast<int>(TileMin); i <= static_cast<int>(TileMax); i++)
    {
        auto state = static_cast<TileState>(i);
        for (int j = 0; j < tileStartAmounts[i]; j++)
        {
            RandomUtils::get_random_tile(_grid, state);
        }
    }
}

void TileMap::tick()
{
    std::vector<Position> occupied = _grid.get_occupied();

    for (Position pos : occupied) {
        if (auto actor = _grid.get(pos)->getActor()) {
            actor->act(pos, _grid);
            _grid.get(pos)->setActor(std::move(actor));
        }
    }
}


int TileMap::get_rabbit_count() const
{
    return _grid._rabbitCount;
}

int TileMap::get_fox_count() const
{
    return _grid._foxCount;
}

Grid & TileMap::get_tile_grid()
{
    return _grid;
}

