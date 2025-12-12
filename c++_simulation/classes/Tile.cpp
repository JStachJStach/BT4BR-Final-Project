#include "../headers/Tile.h"

#include "../headers/RandomUtils.h"
int Tile::_tileID = 0;

/**
 * Default Constructor
 */
Tile::Tile() : _color(RAYWHITE)
{
}

/**
 * Basic tile constructor that sets the name and color of the object
 *
 * @param name Name of tile object
 * @param color Color of tile object
 */
Tile::Tile(const std::string& name, const Color& color) : _name(name), _color(color)
{
    _tileID++;
    // Debug string
    std::cout << "Creating tile " << _name << " with ID "  << _tileID <<"\n";
}

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
 * @return New position
 */
std::array<int, 2> Tile::move(const std::array<int, 2> &currentPosition) //move -> generate, and return, new position based on current position
{
    return std::array<int, 2>{currentPosition[0] + RandomUtils::get_random_num(-1,1), currentPosition[1] +
            RandomUtils::get_random_num(-1, 1)
    };        //EXAMPLE
}
/**
 * Print current position to console
 * @param position Current tile position
 */
void Tile::say(const std::array<int, 2>& position)                                        //EXAMPLE
{                                                                       //EXAMPLE
    std::printf("Hello, my position is: (%d, %d)\n", position[0], position[1]);   //EXAMPLE
}                                                                       //EXAMPLE
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
