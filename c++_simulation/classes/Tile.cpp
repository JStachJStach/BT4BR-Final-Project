#include "../headers/Tile.h"

#include "../headers/RandomUtils.h"
int Tile::_tileID = 0;
int Tile::_rabbit_count = 0;
int Tile::_fox_count = 0;
int Tile::_grass_count = 0;

/**********************************************
 *                                            *
 *               Constructors                 *
 *                                            *
 **********************************************/

/**
 * Default Constructor
 */
Tile::Tile() : _color(BLACK)
{
}

/**
 * Basic tile constructor that sets the name, color of the object and count created objects
 *
 * @param name_in Name of tile object
 * @param color Color of tile object
 */
Tile::Tile(const std::string& name_in, const Color& color) : _name(name_in), _color(color)
{
    _tileID++;
    if (_name == "Grass")
    {
        set_state(TileState::Grass);
        _grass_count++;
    }
    if (_name == "Fox")
    {
        set_state(TileState::Fox);
        _fox_count++;
    }
    if (_name == "Rabbit")
    {
        set_state(TileState::Rabbit);
        _rabbit_count++;
    }
    // Debug string
    std::cout << "Creating tile " << _name << " with ID "  << _tileID <<"\n";
}

/**********************************************
 *                                            *
 *                  Methods                   *
 *                                            *
 **********************************************/

/**
 * Draw tile based on position
 * @param currentPosition Current tile position
 */
void Tile::draw(const std::array<int, 2>& currentPosition) const
{
    //tile color should be based on name and state
    DrawRectangle(currentPosition[0] * cellSize, currentPosition[1] * cellSize, cellSize, cellSize, _color);
}
/**
 * Moves, generates and returns new position based on current position
 * @param currentPosition Current tile position
 * @param tileMap Active array of tiles 
 * @return New position
 */
std::array<int, 2> Tile::act(const std::array<int, 2> &currentPosition, std::map<std::array<int, 2>, Tile> &tileMap)
{   
    // Satiation system
    if (this->_name == "Rabbit")
    {
        //depleting satiation
        this->_satiation += rabbitSatPerTick;
        //death
        if (this->_satiation < rabbitMinSat)
        {
            _rabbit_count--;
            tileMap.erase(currentPosition);
            return currentPosition;
        }
        if (this->_satiation > rabbitReproductionSat)
        {
            for (auto pos : RandomUtils::positionsAdjacent(currentPosition))
            {
                if (!tileMap.contains(pos))
                {
                    const Tile* tile = new Tile("Rabbit", GRAY);
                    tileMap[std::array<int, 2>{pos[0], pos[1]}] = *tile;
                    break;
                }
            }
        }
    }



    // Check if there are certain tiles on adjacent positions
    for (auto pos: RandomUtils::positionsAdjacent(currentPosition))
    {
        if (tileMap.contains(pos))
        {
            if (this->_name == "Fox" and tileMap[pos]._name == "Rabbit")
            {
                _rabbit_count--;
                return pos;
            }
            if (this->_name == "Rabbit" and this->_satiation < rabbitMaxSat and tileMap[pos]._name == "Grass")
            {
                this->_satiation += rabbitSatPerGrass;
                if (this->_satiation > rabbitMaxSat)
                {
                    this->_satiation = rabbitMaxSat;
                }
                _grass_count--;
                return pos;
            }
        }
    }

    // Regular move
    int newPositionX = currentPosition[0] + RandomUtils::get_random_num(-1,1),
    newPositionY = currentPosition[1] + RandomUtils::get_random_num(-1,1);
    // Check if new position is in the bounds of the grid
    if (newPositionX < 0 || newPositionX > gridSize - 1)
        newPositionX = currentPosition[0];
    if (newPositionY < 0 || newPositionY > gridSize - 1)
        newPositionY = currentPosition[1];
    // Check if new position is overlapping other tile
    std::array<int, 2> newPosition = std::array<int, 2>{newPositionX, newPositionY};
    if (tileMap.contains(newPosition))
        newPosition = currentPosition;
    return newPosition;
}

/**********************************************
 *                                            *
 *                  Setters                   *
 *                                            *
 **********************************************/

/**
 * Color setter
 * @param newColor New tile color
 */
void Tile::set_color(const Color & newColor)
{
    _color = newColor;
}
/**
 * State setter
 * @param newState New tile state
 */
void Tile::set_state(const TileState & newState)
{
    _state = newState;
}
/**
 * Name setter
 * @param newName New tile name
 */
void Tile::set_name(const std::string & newName)
{
    _name = newName;
}

/**********************************************
 *                                            *
 *                  Getters                   *
 *                                            *
 **********************************************/

/**
 * TileState getter
 * @return current tile state
 */
TileState Tile::get_state() const
{
    return _state;
}
/**
 * Static grass_count getter
 * @return current grass count
 */
int Tile::get_grass_count()
{
    return _grass_count;
}
/**
 * Static rabbit_count getter
 * @return current rabbit count
 */
int Tile::get_rabbit_count()
{
    return _rabbit_count;
}
/**
 * Static fox_count getter
 * @return current fox count
 */
int Tile::get_fox_count()
{
    return _fox_count;
}
/**
 * Color getter
 * @return current color
 */
Color Tile::get_color() const
{
    return _color;
}
/**
 * Name getter
 * @return current name
 */
std::string Tile::get_name() const
{
    return _name;
}
