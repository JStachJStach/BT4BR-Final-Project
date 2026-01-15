#pragma once
#include "settings.h"
#include "global_enums.h"
class Tile_old
{
public:
    Tile_old();
    Tile_old(const std::string&, const Color&);
    void draw(const std::array<int, 2> &) const;
    std::array<int, 2> act(const std::array<int, 2>&, std::map<std::array<int, 2>, Tile_old>&);
    void set_color(const Color&);
    void set_state(const TileState&);
    void set_name(const std::string&);
    [[nodiscard]] TileState get_state() const;
    static int get_grass_count();
    static int get_rabbit_count();
    static int get_fox_count();
    [[nodiscard]] Color get_color() const;
    [[nodiscard]] std::string get_name() const;

    static std::array<int, 2> move_if_target_in_sight(std::array<int, 2>,const std::array<int, 2>&);
private:
    static int _tileID;
    static int _foxCount;
    static int _rabbitCount;
    static int _grassCount;
    int _satiation=0;
    std::string _name;
    Color _color;
    TileState _state = TileState::None;
};