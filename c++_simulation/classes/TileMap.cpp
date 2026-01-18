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
    _cells = _grid.get_occupied();

}

void TileMap::tick()
{
    // Clear requests
    _grid._spreadRequests.clear();
    _grid._rabbitMoveRequests.clear();
    _grid._foxMoveRequests.clear();
    _grid._rabbitReproductionRequests.clear();
    _grid._foxReproductionRequests.clear();

    // Grow and spread grass
    for (const auto& cell : _grid._grassPositions)
    {
        _grid.get(cell)->grow(10);
        if (_grid.get(cell)->_grassShouldSpread)
        {
            _grid._spreadGrass(_grid.get(cell));
        }
    }

    // Move actors
    for (const auto& pos : _cells)
    {
        if (auto actor = _grid.get(pos)->getActor())
        {
            actor->act(pos, _grid, std::move(actor));
        }
    }

    for (const auto position : _grid._spreadRequests)
    {
        _grid.get(position)->seed(10);
        _grid._grassPositions.push_back(position);
    }

    for (const auto [fst, snd]: _grid._rabbitMoveRequests)
    {
        auto actor = _grid.get(fst)->getActor();

        if (!_grid.get(snd)->hasActor())
        {
            _grid.get(snd)->setActor(std::move(actor));
            for (int i = 0; i < _cells.size(); i++)
                if (_cells[i] == fst)
                {
                    _cells[i] = snd;
                }
        }
        else
        {
            _grid.get(fst)->setActor(std::move(actor));
        }

    }
    for (auto position : _grid._foxMoveRequests)
    {

    }
    for (auto snd: _grid._rabbitReproductionRequests | std::views::values)
    {
        if (!_grid.get(snd)->hasActor())
        {
            _grid.addActor(snd, std::make_unique<Rabbit>());
            _cells.push_back(snd);
        }
    }
    _grid._occupied = _cells;
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

