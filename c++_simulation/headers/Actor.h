#pragma once
#include "Cell.h"

class Grid;

class Actor
{
    friend class Cell;
    public:
    virtual ~Actor() = default;

    explicit Actor(
        const TileState& state,
        const int& initialEnergy,
        const int& maxEnergy,
        const int& reproductionThreshold,
        const int& reproductionCost,
        const int& movesPerTick,
        const Color& color)
    :
    _type(state),
    _initialEnergy(initialEnergy),
    _maxEnergy(maxEnergy),
    _reproductionThreshold(reproductionThreshold),
    _reproductionCost(reproductionCost),
    _movesPerTick(movesPerTick),
    _color(color)
    {
    }

    virtual void act(Position pos, Grid& _grid, std::unique_ptr<Actor> actor);
    virtual void tryToEat(Position pos, Grid& _grid);

    // Getters
    TileState type() const noexcept;
    Color getColor() const;


    // Interaction traits
    [[nodiscard]] virtual bool isEdible() const { return false; }
    [[nodiscard]] virtual bool blocksMovement() const { return true; }

protected:
    TileState getType_() const;
    int getInitialEnergy_() const;
    int getMaxEnergy_() const;
    int getReproductionThreshold_() const;
    int getReproductionCost_() const;
    int getMovesPerTick_() const;
    Color getColor_() const;
    void setAlive_(const bool& isAlive);
    virtual void eat();
    virtual void die();
    virtual void move(const Position& pos_old, const Position& pos_new, Grid &_grid, std::unique_ptr<Actor> actor);
private:
    TileState _type;
    int _initialEnergy{};
    int _maxEnergy{};
    int _reproductionThreshold{};
    int _reproductionCost{};
    int _movesPerTick{};
    Color _color{};
    bool _alive = true;
};

