#pragma once
#include "settings.h"
#include "global_enums.h"
class Tile
{
public:
    Tile();
    Tile(const std::string&, const Color&);
    void draw(const std::array<int, 2> &) const;
    std::array<int, 2> move(const std::array<int, 2>&, std::map<std::array<int, 2>, Tile>&);
    void say(const std::array<int, 2>&);
    void set_color(const Color&);
    void set_state(const TileState&);
    void set_name(const std::string&);
    TileState get_state() const;
    static int fox_count;
    static int rabbit_count;
    static int grass_count;
    std::string name;
private:
    static int _tileID;
    Color _color;
    TileState _state = TileState::None;
};