#pragma once

#include <vector>
#include <memory>
#include <stdexcept>

#include "Actor.h"
#include "global_enums.h"

class Grid
{
    friend class TileMap;
public:

    [[nodiscard]] int width()  const noexcept { return width_; }
    [[nodiscard]] int height() const noexcept { return height_; }

    // Queries
    [[nodiscard]] bool inBounds(Position pos) const noexcept;
    [[nodiscard]] bool isEmpty(Position pos) const;
    [[nodiscard]] Cell* get(Position pos) const;
    [[nodiscard]] int getGrassLevel(Position pos) const;

    // Modification
    void addActor(Position pos, std::unique_ptr<Actor> actor);

    void moveActor(Position pos, std::unique_ptr<Actor> actor) const;

    void removeActor(Position pos);
    void eat(Position pos) const;

    std::vector<Position> get_cells() const;
    std::vector<Position> get_occupied() const;
    void draw() const;
    void appendGrassPos(Position pos);
    void appendReproductionRequest(Position parentPos, Position childPos, TileState tileState);
    void appendMoveRequest(const Position& pos_old, const Position &pos_new, const TileState& tileState);
private:
    Grid(int width, int height);
    [[nodiscard]] std::size_t index(Position pos) const;
    void _modifyAmounts(bool subtract,  std::unique_ptr<Actor> actor, Position pos);
    void _spreadGrass(const Cell* cell);

    int _foxCount = 0;
    int _rabbitCount = 0;
    int width_;
    int height_;

    std::vector<Position> _spreadRequests{};
    std::vector<std::pair<Position,Position>> _rabbitMoveRequests{};
    std::vector<std::pair<Position,Position>> _rabbitReproductionRequests{};
    std::vector<std::pair<Position,Position>> _foxMoveRequests{};
    std::vector<std::pair<Position,Position>> _foxReproductionRequests{};
    std::vector<Position> _eatRequests{};
    std::vector<Position> _grassPositions{};
    std::vector<std::unique_ptr<Cell>> _cells;
    std::vector<Position> _occupied{};
};