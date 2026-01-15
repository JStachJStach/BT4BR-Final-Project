#include "../headers/Grid.h"
#include "../headers/Rabbit.h"
Grid::Grid(int width, int height)
    : width_(width),
      height_(height),
      cells_(width * height)
{
    for (int y = 0; y < height_; ++y)
        for (int x = 0; x < width_; ++x)
            cells_[y * width_ + x] = std::make_unique<Cell>();
    //Debug

    addActor({0,0}, std::make_unique<Rabbit>());

}

bool Grid::inBounds(const Position pos) const noexcept
{
    return pos.x_pos >= 0 && pos.x_pos < width_
        && pos.y_pos >= 0 && pos.y_pos < height_;
}

std::size_t Grid::index(const Position pos) const
{
    return static_cast<std::size_t>(pos.y_pos * width_ + pos.x_pos);
}

void Grid::_modifyAmounts(const bool subtract, std::unique_ptr<Actor> actor, Position pos)
{
    int modifyAmount = 1;
    if (subtract)
    {
        modifyAmount *= -1;
    }
    switch (actor->type())
    {
        case TileState::Rabbit:
        {
            _rabbitCount += modifyAmount;
            cells_[index(pos)]->setActor(std::move(actor));
            break;
        }
        case TileState::Fox:
        {
            _foxCount += modifyAmount;
            cells_[index(pos)]->setActor(std::move(actor));
            break;
        }
        default: break;
    }
}

bool Grid::isEmpty(const Position pos) const
{
    if (!inBounds(pos))
        throw std::out_of_range("Grid::isEmpty: position out of bounds");

    return !cells_[index(pos)]->hasActor();
}

Cell* Grid::get(const Position pos) const
{
    if (!inBounds(pos))
        throw std::out_of_range("Grid::get: position out of bounds");

    return cells_[index(pos)].get();
}

void Grid::addActor(const Position pos, std::unique_ptr<Actor> actor)
{
    if (!inBounds(pos))
        throw std::out_of_range("Grid::addTile: position out of bounds");

    if (!isEmpty(pos))
        throw std::logic_error("Grid::addTile: cell already occupied");

    _modifyAmounts(false, std::move(actor), pos);
    cells_[index(pos)]->setActor(std::move(actor));

}

void Grid::removeCell(const Position pos)
{
    if (!inBounds(pos))
        throw std::out_of_range("Grid::removeTile: position out of bounds");

    cells_[index(pos)].reset();
    _modifyAmounts(true, std::move(cells_[index(pos)]->getActor()), pos);

}
// Not sure if this is needed tbh
std::unique_ptr<Cell> Grid::takeTile(const Position pos)
{
    if (!inBounds(pos))
        throw std::out_of_range("Grid::takeTile: position out of bounds");

    auto& cell = cells_[index(pos)];
    return std::move(cell);
}

std::vector<Position> Grid::get_occupied() const
{
    std::vector<Position> occupied;
    for (int y = 0; y < height_; ++y)
        for (int x = 0; x < width_; ++x)
            if (!this->isEmpty({x,y}))
            {
                Position pos{x,y};
                occupied.push_back(pos);
            }
    return occupied;
}
