#include "../headers/Grid.h"

Grid::Grid(int width, int height)
    : width_(width),
      height_(height),
      cells_(width * height)
{
}

bool Grid::inBounds(Position pos) const noexcept
{
    return pos.x_pos >= 0 && pos.x_pos < width_
        && pos.y_pos >= 0 && pos.y_pos < height_;
}

std::size_t Grid::index(Position pos) const
{
    return static_cast<std::size_t>(pos.y_pos * width_ + pos.x_pos);
}

void Grid::_modifyAmounts(const bool subtract, const std::unique_ptr<Tile> &tile)
{
    int modifyAmount = 1;
    if (subtract)
    {
        modifyAmount *= -1;
    }
    switch (tile->type())
    {
        case TileState::Grass:
        {
            _grassCount += modifyAmount;
            break;
        }
        case TileState::Rabbit:
        {
            _rabbitCount += modifyAmount;
            break;
        }
        case TileState::Fox :
        {
            _foxCount += modifyAmount;
            break;
        }
        default: break;
    }
}

bool Grid::isEmpty(const Position pos) const
{
    if (!inBounds(pos))
        throw std::out_of_range("Grid::isEmpty: position out of bounds");

    return cells_[index(pos)] == nullptr;
}

Tile* Grid::get(const Position pos) const
{
    if (!inBounds(pos))
        throw std::out_of_range("Grid::get: position out of bounds");

    return cells_[index(pos)].get();
}

void Grid::addTile(const Position pos, std::unique_ptr<Tile> tile)
{
    if (!inBounds(pos))
        throw std::out_of_range("Grid::addTile: position out of bounds");

    if (!isEmpty(pos))
        throw std::logic_error("Grid::addTile: cell already occupied");

    cells_[index(pos)] = std::move(tile);
    _modifyAmounts(false, std::move(cells_[index(pos)]));
}

void Grid::removeTile(const Position pos)
{
    if (!inBounds(pos))
        throw std::out_of_range("Grid::removeTile: position out of bounds");

    cells_[index(pos)].reset();
    _modifyAmounts(true, std::move(cells_[index(pos)]));
}
// Not sure if this is needed tbh
std::unique_ptr<Tile> Grid::takeTile(const Position pos)
{
    if (!inBounds(pos))
        throw std::out_of_range("Grid::takeTile: position out of bounds");

    auto& cell = cells_[index(pos)];
    return std::move(cell);
}

std::vector<Position> Grid::get_occupied() const
{
    std::vector<Position> occupied;
    for (int y = 0; y < this->height(); ++y)
        for (int x = 0; x < this->width(); ++x)
            if (!this->isEmpty({x,y}))
            {
                Position pos{x,y};
                occupied.push_back(pos);
            }
    return occupied;
}
