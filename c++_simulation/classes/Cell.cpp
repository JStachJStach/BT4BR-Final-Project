#include "../headers/Cell.h"
#include "../headers/Actor.h"

Cell::Cell()
{
    _grassLevel = 0;
    _grassMAX = grassMaxAmount;
}

bool Cell::hasActor() const
{
    if (_actor == nullptr)
    {
        return false;
    }
    return true;
}

void Cell::setActor(std::unique_ptr<Actor> actor)
{
    _actor = std::move(actor);
}

void Cell::setPosition(const Position &position)
{
    _currentPosition.x_pos = position.x_pos;
    _currentPosition.y_pos = position.y_pos;
}

std::unique_ptr<Actor> Cell::getActor()
{

    return std::move(_actor);
}


void Cell::draw(const Position& currentPosition) const
{
    if (_actor != nullptr)
    {
        Color test = _actor->getColor();
        DrawRectangle(currentPosition.x_pos * cellSize, currentPosition.y_pos * cellSize, cellSize, cellSize, test);
    }
    else
    {
        DrawRectangle(currentPosition.x_pos * cellSize, currentPosition.y_pos * cellSize, cellSize, cellSize, _grassColorSaturation);
    }
}

void Cell::grow(const int& howMuch)
{
    if (_grassLevel + howMuch < _grassMAX)
        _grassLevel += howMuch;
    else
    {
        _grassLevel = _grassMAX;
    }
}

void Cell::_setGrassSatColor()
{
    _grassColorSaturation.g = (_grassLevel * 255/_grassMAX);
}

void Cell::_setColor()
{
    _color = _actor->color_;
}
