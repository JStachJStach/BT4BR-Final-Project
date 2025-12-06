#pragma once
#include "settings.h"
#include "global_enums.h"
class Tile
{
public:
    Tile();
    Tile(const std::string&, const Color&);
    void draw(const std::array<int, 2> &) const;
    std::array<int, 2> move(std::array<int, 2>);
    void say(const std::array<int, 2>&);
    void setColor(const Color&);
    void setState(const TileState&);
    void setName(const std::string&);
private:
    std::string _name;   //tiles have names
    Color _color;        //and colors
    TileState _state = TileState::None;      //and state, that should determine tile behavior, to be done in a future
};