#pragma once
#include "settings.h"
#include "Position.h"

class Actor;

class Cell
{
public:

    Cell();
    ~Cell() = default;
    bool hasActor() const;
    void setActor(std::unique_ptr<Actor>  actor);
    std::unique_ptr<Actor> getActor();
    // Rendering
    void draw(const Position &) const;
    void grow(const int &howMuch);

private:
    std::unique_ptr<Actor> _actor = nullptr;
    Color _color{};
    int _grassLevel = 0; //(0 - MAX)
    int _grassMAX = grassMaxAmount; //(0 - MAX)
    Color _grassColorSaturation = RAYWHITE; //(0 - 255) based on _grassLevel * 255/Max

    void _setGrassSatColor();
    void _setColor(); // Convert _grassColorSaturation -> Color

};


