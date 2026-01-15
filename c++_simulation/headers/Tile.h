#pragma once
#include "settings.h"
#include "Position.h"

class Grid;

class Tile
{
public:
    Tile() = default;
    explicit Tile(const Color color) : color_(color) {};
    virtual ~Tile() = default;

    // Called once per simulation tick
    virtual void act(Position pos, Grid& _grid) = 0;
    virtual TileState type() const noexcept = 0;

    // Interaction traits
    [[nodiscard]] virtual bool isEdible() const { return false; }

    // Rendering
    void draw(const Position &) const;
    protected:
    Color color_{};
};


