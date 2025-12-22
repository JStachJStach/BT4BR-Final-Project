#pragma once
#include "settings.h"
#include "global_enums.h"
class Tile
{
public:
    Tile();
    Tile(const std::string&, const Color&);
    void draw(const std::array<int, 2> &) const;
    std::array<int, 2> act(const std::array<int, 2>&, std::map<std::array<int, 2>, Tile>&);
    void set_color(const Color&);
    void set_state(const TileState&);
    void set_name(const std::string&);
    [[nodiscard]] TileState get_state() const;
    static int get_grass_count();
    static int get_rabbit_count();
    static int get_fox_count();
    [[nodiscard]] Color get_color() const;
    [[nodiscard]] std::string get_name() const;

private:
    static int _tileID;
    static int _fox_count;
    static int _rabbit_count;
    static int _grass_count;
    int _satiation=0;
    std::string _name;
    Color _color;
    TileState _state = TileState::None;
};