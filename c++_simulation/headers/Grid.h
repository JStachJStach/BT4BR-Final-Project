#pragma once

#include <vector>
#include <memory>
#include <stdexcept>

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
    [[nodiscard]] std::unique_ptr<Cell> get(Position pos);

    // Modification
    void addActor(Position pos, std::unique_ptr<Actor> actor);
    void removeCell(Position pos);
    std::unique_ptr<Cell> takeTile(Position pos);
    std::vector<Position> get_occupied() const;

private:
    Grid(int width, int height);
    [[nodiscard]] std::size_t index(Position pos) const;
    void _modifyAmounts(bool subtract, const Actor & actor);

    int _foxCount = tileStartAmounts[static_cast<int>(TileState::Fox)];
    int _rabbitCount = tileStartAmounts[static_cast<int>(TileState::Rabbit)];
    int width_;
    int height_;
    std::vector<std::unique_ptr<Cell>> cells_;
};