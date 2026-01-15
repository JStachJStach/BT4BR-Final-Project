#pragma once
#include "settings.h"
#include "RandomUtils.h"


#include "Grid.h"

class TileMap
{
public:
    TileMap();
    void tick();
    int get_grass_count() const;
    int get_rabbit_count() const;
    int get_fox_count() const;
    Grid& get_tile_grid();
private:
    Grid _grid;
    void _addTile(Position pos, std::unique_ptr<Tile> tile);

};
