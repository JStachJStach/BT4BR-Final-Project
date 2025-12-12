#include <ranges>
#include <algorithm>
#include "headers/settings.h"
#include "headers/RandomUtils.h"
#include "headers/global_enums.h"
#include "headers/Tile.h"
RandomUtils RandomUtils;

/**
 * Check if the tile position given already exists in the tilemap???? Kuba please fact check me on this
 * @param tilePosition Tile position
 * @param tileMap Current state of the tilemap
 * @return
 */
bool OnTile(const std::array<int, 2> &tilePosition, const std::map<std::array<int, 2>, Tile> &tileMap) //this functions is (will be) used to check if there is any tile on given position. So the tiles won't overlap.
{
    if (!tileMap.contains(tilePosition))
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

void DrawTiles(std::map<std::array<int, 2>, Tile> tileMap) //this function calls draw methods of all tiles in tilemap
{
    for (const auto &position: tileMap | std::views::keys)
    {
        tileMap[position].draw(position);
    }
}

int main()
{
    // Really important save_seed() is called first, please do not mess with this :)
    RandomUtils.save_seed();
    save_settings();
    ///////////////////////////////////
    // Initialization
    ///////////////////////////////////

    std::map<std::array<int, 2>, Tile> tileMap; //creating empty tilemap
    // Set loop bounds
    constexpr TileState TileMin = TileState::Grass;
    constexpr TileState TileMax = TileState::Fox;
    // Iterate over the enum class and create tiles based on settings
    for (auto i = static_cast<int>(TileMin); i <= static_cast<int>(TileMax); i++)
    {
        TileState state = static_cast<TileState>(i);
        for (int j = 0; j < tileStartAmounts[i - 1]; j++)
        {
            RandomUtils.get_random_tile(tileMap, state);
        }
    }

    double lastTickTime = 0; //this is necessary to perform tick update (look at the statement ( if (lastTickTime + tickDuration < GetTime()) ) )
    InitWindow(screenWidth, screenHeight, "Simulation");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        ///////////////////////////////////
        // Update per tick
        ///////////////////////////////////

        if (lastTickTime + tickDuration < GetTime()) //this condition is fulfilled only once per tickDuration
        {
            std::vector<std::array<int, 2>> tilesPositions; //tilesPosition is made to make the choice of position unbiased (e.g. not from left to right)
            for (const auto &key: tileMap | std::views::keys)
            {
                tilesPositions.push_back(key); //tilesPositon contains all positions that are stored in the map
            }
            std::shuffle(tilesPositions.begin(), tilesPositions.end(), rng); //tilesPositon is being shuffled
            for (auto pos : tilesPositions) //positions from tilePosition are in random order so the order of movement is undetermined
            {
                std::array<int, 2> newPos = tileMap[pos].move(pos); //.move(pos) means: generate new position of tile based on the old position (argument) and tile type (Tile.name stored in struct)
                tileMap[pos].say(pos);                      //EXAMPLE
                if (newPos != pos) //if moved: remove old pos from the map
                {
                    tileMap[newPos] = tileMap[pos];
                    tileMap.erase(pos);
                }
            }
            lastTickTime = GetTime(); //look at the statement ( if (lastTickTime + tickDuration < GetTime()) )
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