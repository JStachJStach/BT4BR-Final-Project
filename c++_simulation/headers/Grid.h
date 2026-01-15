#pragma once

#include <vector>
#include <memory>
#include <stdexcept>

#include "Grass.h"
#include "Actor.h"


class Grid
{
    friend class TileMap;
public:

    [[nodiscard]] int width()  const noexcept { return width_; }
    [[nodiscard]] int height() const noexcept { return height_; }

    // Queries
    [[nodiscard]] bool inBounds(Position pos) const noexcept;
    [[nodiscard]] bool isEmpty(Position pos) const;
    [[nodiscard]] Tile* get(Position pos) const;

    // Modification
    void addTile(Position pos, std::unique_ptr<Tile> tile);
    void removeTile(Position pos);
    std::unique_ptr<Tile> takeTile(Position pos);
    std::vector<Position> get_occupied() const;

private:
    Grid(int width, int height);
    [[nodiscard]] std::size_t index(Position pos) const;
    void _modifyAmounts(bool subtract, const std::unique_ptr<Tile> &tile);
    int _foxCount = tileStartAmounts[static_cast<int>(TileState::Fox)];
    int _grassCount = tileStartAmounts[static_cast<int>(TileState::Grass)];
    int _rabbitCount = tileStartAmounts[static_cast<int>(TileState::Rabbit)];
    int width_;
    int height_;
    std::vector<std::unique_ptr<Tile>> cells_;
};