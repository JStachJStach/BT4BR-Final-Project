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
double tickDuration = 0.3;
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
    Color color;
    int state = 0;
    void draw(std::array<int, 2> pos)
    {
        //tile color based on name and state
        DrawRectangle(pos[0] * cellSize, pos[1] * cellSize, cellSize, cellSize, color);
    }
    std::array<int, 2> move(std::array<int, 2> currentPos)
    {
        return std::array<int, 2>{currentPos[0] + 1, currentPos[1]};        //EXAMPLE
    }                                         
    void say(std::array<int, 2> pos)                                        //EXAMPLE
    {                                                                       //EXAMPLE
        std::printf("Hello, my position is: (%d, %d)\n", pos[0], pos[1]);   //EXAMPLE
    }                                                                       //EXAMPLE
};

bool OnTile(std::array<int, 2> pos, std::map<std::array<int, 2>, Tile> map)
{
    if (map.find(pos) == map.end())
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
    for (auto const& [pos, val] : map)
    {
        map[pos].draw(pos);
    }
}

int main()
{
    ///////////////////////////////////
    // Initialization
    ///////////////////////////////////

    std::map<std::array<int, 2>, Tile> tileMap;             //EXAMPLE
    Tile testTile;                                          //EXAMPLE
    testTile.color = DARKBLUE;                              //EXAMPLE
    tileMap[std::array<int, 2>{1, 2}] = testTile;           //EXAMPLE, to be replaced with randomly initialized, functional tiles

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
            std::vector<std::array<int, 2>> tilesPositions; //tilesPosition is made to make the choice of pos unbiased (e.g. not from left to right)
            for (auto const& [key, val] : tileMap)
            {
                tilesPositions.push_back(key);
            }
            std::shuffle(tilesPositions.begin(), tilesPositions.end(), rng);
            for (auto pos : tilesPositions)
            {
                std::array<int, 2> newPos = tileMap[pos].move(pos);
                tileMap[pos].say(pos);                      //EXAMPLE
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
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
}