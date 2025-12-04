#include <algorithm>
#include "raylib.h"
#include <random>
#include <array>
#include <map>

///////////////////////////////////
// Settings
///////////////////////////////////

const int screenWidth = 1200;
const int screenHeight = 1200;
double tickDuration = 0.03;
// Grid
const unsigned int gridSize = 60;
const unsigned int cellSize = screenWidth / gridSize;
const unsigned int gridLineThickness = 2;
Color gridLineColor = LIGHTGRAY;
// Start Values
std::random_device dev;
std::mt19937 rng(dev());
//std::uniform_int_distribution<std::mt19937::result_type> distOnGrid(0, gridSize - 1);

struct Tile
{
    std::string name;
    Color tileColor;
    int state = 0;
    void draw(std::array<int, 2> pos)
    {
        //tile color based on name and state
        DrawRectangle(pos[0] * cellSize, pos[1] * cellSize, cellSize, cellSize, tileColor);
    }
};

bool OnTile(std::array<int, 2> key, std::map<std::array<int, 2>, Tile> map)
{
    if (map.find(key) == map.end())
    {
        return false;
    }
    return true;
}



void DrawGrid()
{
    Vector2 startPos;
    Vector2 endPos;
    for (unsigned int i = 0; i != gridSize + 1; i++)
    {
        // vertically
        startPos.x = cellSize * i;
        startPos.y = 0;
        endPos.x = cellSize * i;
        endPos.y = cellSize * gridSize;
        DrawLineEx(startPos, endPos, gridLineThickness, gridLineColor);
        // horizontally
        startPos.x = 0;
        startPos.y = cellSize * i;
        endPos.x = cellSize * gridSize;
        endPos.y = cellSize * i;
        DrawLineEx(startPos, endPos, gridLineThickness, gridLineColor);
    }
}

void DrawTiles(std::map<std::array<int, 2>, Tile> map)
{
    for (auto const& [key, val] : map)
    {
        map[key].draw(key);
    }
}

int main()
{
    ///////////////////////////////////
    // Initialization
    ///////////////////////////////////

    std::map<std::array<int, 2>, Tile> tileMap;

    double lastTickTime = 0;
    InitWindow(screenWidth, screenHeight, "Simulation");
    SetTargetFPS(60);


    while (!WindowShouldClose())
    {
        ///////////////////////////////////
        // Update per tick
        ///////////////////////////////////

        if (lastTickTime + tickDuration < GetTime())
        {
            std::vector<std::array<int, 2>> tilesPositions; //tilesPosition is where new positions are going to be created
            for (auto const& [key, val] : tileMap)
            {
                tilesPositions.push_back(key);
            }
            std::shuffle(tilesPositions.begin(), tilesPositions.end(), rng); //making choice of tile unbiased
            for (auto pos : tilesPositions)
            {
                std::array<int, 2> newPos = pos;
                // if "tile something" do "move somewhere"
                if (newPos != pos)
                {
                    tileMap[newPos] = tileMap[pos];
                    tileMap.erase(pos);
                }
            }
            lastTickTime = GetTime();
        }

        ///////////////////////////////////
        // Draw
        ///////////////////////////////////

        BeginDrawing();
        DrawGrid();
        DrawTiles(tileMap);
        DrawTiles(tileMap);
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
}