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

void Cell::grow(const int& howMuch) //Change magic numbers to variables
{
    if (_grassLevel > 0)
    {
        if (_grassLevel + howMuch < _grassMAX)
            _grassLevel += howMuch;
        else
        {
            _grassLevel = _grassMAX;
        }
        _setGrassSatColor();
    }
    if (_grassLevel > 90)
    {
        _grassShouldSpread = true;
    }
}

void Cell::seed(const int& howMuch)
{
    _grassLevel += howMuch;
}

void Cell::_setGrassSatColor()
{
    _grassColorSaturation = grassColor_.calculateGrassColor(_grassLevel);
}

void Cell::_setColor()
{
    _color = _actor->_color;
}
