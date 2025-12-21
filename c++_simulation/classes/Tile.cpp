#include "../headers/Tile.h"

#include "../headers/RandomUtils.h"
int Tile::_tileID = 0;
int Tile::rabbit_count = 0;
int Tile::fox_count = 0;
int Tile::grass_count = 0;

std::array<std::array<int, 2>, 8> positionsAdjacent = std::array<std::array<int, 2>, 8>{
        std::array<int, 2>{-1, -1},
        std::array<int, 2>{-1, 0},
        std::array<int, 2>{-1, 1},
        std::array<int, 2>{0, -1},
        std::array<int, 2>{0, 1},
        std::array<int, 2>{1, -1},
        std::array<int, 2>{1, 0},
        std::array<int, 2>{1, 1}
};


/**
 * Default Constructor
 */
Tile::Tile() : _color(RAYWHITE)
{
}

/**
 * Basic tile constructor that sets the name, color of the object and count created objects
 *
 * @param name Name of tile object
 * @param color Color of tile object
 */
Tile::Tile(const std::string& name_in, const Color& color) : name(name_in), _color(color)
{
    _tileID++;
    if (name == "Grass")
    {
        set_state(TileState::Grass);
        grass_count++;
    }
    if (name == "Fox")
    {
        set_state(TileState::Fox);
        fox_count++;
    }
    if (name == "Rabbit")
    {
        set_state(TileState::Rabbit);
        rabbit_count++;
    }
    // Debug string
    std::cout << "Creating tile " << name << " with ID "  << _tileID <<"\n";
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
 * @param tileMap Active array of tiles 
 * @return New position
 */
std::array<int, 2> Tile::move(const std::array<int, 2> &currentPosition, std::map<std::array<int, 2>, Tile> &tileMap)
{   
    // Check if there are certain tiles on adjacent positions
    for (auto positionAdj : positionsAdjacent)
    {
        positionAdj[0] += currentPosition[0];
        positionAdj[1] += currentPosition[1];
        if (tileMap.contains(positionAdj))
        {
            if (this->name == "Fox" and tileMap[positionAdj].name == "Rabbit")
            {
                tileMap.erase(positionAdj);
                rabbit_count--;
                return positionAdj;
            }
            if (this->name == "Rabbit" and tileMap[positionAdj].name == "Grass")
            {
                grass_count--;
                return positionAdj;
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
    name = newName;
}

TileState Tile::get_state() const
{
    return _state;
}
