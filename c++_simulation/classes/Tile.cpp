#include "../headers/Tile.h"


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
    // Debug string
    std::cout << "Creating tile " << _name << "\n";
}

/**
 * Draw tile based on position
 * @param position Current tile position
 */
void Tile::draw(const std::array<int, 2>& position) const
{
    //tile color should be based on name and state
    DrawRectangle(position[0] * cellSize, position[1] * cellSize, cellSize, cellSize, _color);
}
/**
 * Moves, generates and returns new position based on current position
 * @param currentPosition Current tile position
 * @return New position
 */
std::array<int, 2> Tile::move(std::array<int, 2> currentPosition) //move -> generate, and return, new position based on current position
{
    return std::array<int, 2>{currentPosition[0] + 1, currentPosition[1]};        //EXAMPLE
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
void Tile::setColor(const Color & newColor)
{
    _color = newColor;
}
/**
 * State setter
 * @param newState New tile state
 */
void Tile::setState(const TileState & newState)
{
    _state = newState;
}
/**
 * Name setter
 * @param newName New tile name
 */
void Tile::setName(const std::string & newName)
{
    _name = newName;
}
