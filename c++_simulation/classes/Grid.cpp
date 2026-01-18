#include "../headers/Grid.h"

#include <format>

#include "../headers/Rabbit.h"
#include "../headers/RandomUtils.h"

Grid::Grid(const int width, const int height)
    : width_(width/cellSize),
      height_(height/cellSize),
      _cells(width/cellSize * height/cellSize)
{
    for (int y = 0; y < height_; ++y)
        for (int x = 0; x < width_; ++x)
        {
            _cells[y * width_ + x] = std::make_unique<Cell>();
            _cells[index({x, y})]->setPosition({x,y});
        }
    //Debug

    addActor({0,0}, std::make_unique<Rabbit>());
    _cells[index({0,0})]->seed(90);
}

bool Grid::inBounds(const Position pos) const noexcept
{
    return (pos.x_pos >= 0 && pos.x_pos < width_) && (pos.y_pos >= 0 && pos.y_pos < height_);
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
            _cells[index(pos)]->setActor(std::move(actor));
            break;
        }
        case TileState::Fox:
        {
            _foxCount += modifyAmount;
            _cells[index(pos)]->setActor(std::move(actor));
            break;
        }
        default: break;
    }
}

void Grid::_spreadGrass(const Cell* cell)
{
    const std::vector<Position> positions = RandomUtils::positionsAdjacent(cell->_currentPosition);
    for (const auto &pos : positions)
    {
        if (inBounds(pos))
        {
            if (get(pos)->_grassLevel == 0)
            {
                _spreadRequests.push_back(pos);
                return;
            }
        }
    }
}

bool Grid::isEmpty(const Position pos) const
{
    if (!inBounds(pos))
        throw std::out_of_range("Grid::isEmpty: position out of bounds");

    return !_cells[index(pos)]->hasActor();
}

Cell* Grid::get(const Position pos) const
{
    if (!inBounds(pos))
        throw std::out_of_range("Grid::get: position out of bounds");

    return _cells[index(pos)].get();
}

int Grid::getGrassLevel(const Position pos) const
{
    return _cells[index(pos)]->_grassLevel;
}

void Grid::addActor(const Position pos, std::unique_ptr<Actor> actor)
{
    if (!inBounds(pos))
        throw std::out_of_range("Grid::addTile: position out of bounds");

    if (!isEmpty(pos))
        throw std::logic_error("Grid::addTile: cell already occupied");

    _modifyAmounts(false, std::move(actor), pos);

}
void Grid::moveActor(const Position pos, std::unique_ptr<Actor> actor) const
{
    if (!inBounds(pos))
        throw std::out_of_range("Grid::moveTile: position out of bounds");

    if (!isEmpty(pos))
        throw std::logic_error("Grid::moveTile: cell already occupied");
    _cells[index(pos)]->setActor(std::move(actor));
}
void Grid::removeActor(const Position pos)
{
    if (!inBounds(pos))
        throw std::out_of_range("Grid::removeTile: position out of bounds");

    _modifyAmounts(true, std::move(_cells[index(pos)]->getActor()), pos);
    _cells[index(pos)].reset();

}

void Grid::eat(const Position pos) const
{
    get(pos)->_grassLevel -= 5;
}



std::vector<Position> Grid::get_cells() const
{
    std::vector<Position> cells;
    for (const auto &cell : _cells)
    {
        cells.push_back(cell->_currentPosition);
    }
    return cells;
}

std::vector<Position> Grid::get_occupied() const
{
    std::vector<Position> cells;
    for (const auto &cell : _cells)
    {
        if (cell->hasActor())
            cells.push_back(cell->_currentPosition);
    }
    return cells;
}



void Grid::draw() const
{
    for (const auto& grass_position : _grassPositions)
    {
        const auto cell = get(grass_position);
        const Color temp = cell->_grassColorSaturation;
        if (temp.r != RAYWHITE.r && temp.g != RAYWHITE.g && temp.b != RAYWHITE.b)
            DrawRectangle(cell->_currentPosition.x_pos * cellSize, cell->_currentPosition.y_pos * cellSize, cellSize, cellSize,  cell->_grassColorSaturation);
    }
    for (const auto& cell : _occupied)
    {
        auto actor = get(cell)->getActor();
        if (actor)
        {
            const Color col = actor->getColor();
            DrawRectangle(cell.x_pos * cellSize, cell.y_pos * cellSize, cellSize, cellSize, col);
            get(cell)->setActor(std::move(actor));
        }
        // ;
        // const Color test = actor->getColor();}
    }
}
void Grid::appendGrassPos(const Position pos)
{
    _grassPositions.push_back(pos);
}

void Grid::appendReproductionRequest(Position parentPos, Position childPos, TileState tileState)
{
    switch (tileState)
    {
        case TileState::Rabbit:
        {
            _rabbitReproductionRequests.push_back({parentPos, childPos});
            break;
        }
        case TileState::Fox:
        {
            _foxReproductionRequests.push_back({parentPos, childPos});
            break;
        }
        default:
        {
            break;
        }

    }
}

void Grid::appendMoveRequest(const Position& pos_old, const Position &pos_new, const TileState& tileState)
{
    switch (tileState)
    {
        case TileState::Rabbit:
        {
            _rabbitMoveRequests.push_back({pos_old, pos_new});
            break;
        }
        case TileState::Fox:
        {
            _foxMoveRequests.push_back({pos_old, pos_new});
            break;
        }
        default: break;
    }
}