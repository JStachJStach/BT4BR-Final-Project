#pragma once
#include "settings.h"
#include "global_enums.h"
class Tile
{
public:
    Tile();
    Tile(const std::string&, const Color&);
    void draw(const std::array<int, 2> &) const;
    std::array<int, 2> move(const std::array<int, 2>&, const std::map<std::array<int, 2>, Tile>&);
    void say(const std::array<int, 2>&);
    void set_color(const Color&);
    void set_state(const TileState&);
    void set_name(const std::string&);
    TileState get_state() const;
    static int fox_count;
    static int rabbit_count;
    static int grass_count;
private:
    static int _tileID;
    std::string _name;   //tiles have names
    Color _color;        //and colors
    TileState _state = TileState::None;      //and state, that should determine tile behavior, to be done in a future
};