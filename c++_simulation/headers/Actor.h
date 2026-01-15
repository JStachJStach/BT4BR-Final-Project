#pragma once
#include "Cell.h"

class Grid;

class Actor
{
    friend class Cell;
    public:
    virtual ~Actor() = default;

    explicit Actor(const Color color) : color_(color) {}

    virtual void act(Position pos, Grid& _grid);
    virtual TileState type() const noexcept;

    // Interaction traits
    [[nodiscard]] virtual bool isEdible() const { return false; }
    [[nodiscard]] virtual bool blocksMovement() const { return true; }
private:
    Color color_{};
};

