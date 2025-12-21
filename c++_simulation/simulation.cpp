#include <ranges>


#include "headers/GrassUtils.h"
#include "headers/settings.h"
#include "headers/RandomUtils.h"
#include "headers/global_enums.h"
#include "headers/Tile.h"
RandomUtils randomUtils;


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
    randomUtils.save_seed();
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
            RandomUtils::get_random_tile(tileMap, state);
        }
    }
    double lastTickTime = 0; //this is necessary to perform tick update (look at the statement ( if (lastTickTime + tickDuration < GetTime()) ) )
    InitWindow(screenWidth, screenHeight, "Simulation");
    SetTargetFPS(60);

    //saving data to csv file per tick 
    std::fstream data_file;
    data_file.open("../data/raw/data.csv", std::ios::out | std::ios::trunc);
    if (data_file.is_open())
    {
        data_file << "lastTickTime" << "," << "Tile::grass_count" << "," << "Tile::rabbit_count" << "," << "Tile::fox_count" << std::endl;
    }

    std::vector<std::array<int, 2>> tilesPositions; // tilesPosition is made to make the choice of position unbiased (e.g. not from left to right)
    std::vector<std::array<int, 2>> grassPositions; // separate Array for grass since it shouldn't move

    while (!WindowShouldClose())
    {
        ///////////////////////////////////
        // Update per tick
        ///////////////////////////////////

        if (lastTickTime + tickDuration < GetTime()) //this condition is fulfilled only once per tickDuration
        {
            tilesPositions.clear();
            grassPositions.clear();

            // get tile positons
            for (const auto &key: tileMap | std::views::keys)
            {
                if (tileMap.at(key).get_state() != TileState::Grass)
                    tilesPositions.push_back(key); //tilesPositon contains all positions that are stored in the map
                else
                    grassPositions.push_back(key);
            }

            std::ranges::shuffle(tilesPositions, rng); //tilesPositon is being shuffled

            for (auto pos : tilesPositions) //positions from tilePosition are in random order so the order of movement is undetermined
            {
                std::array<int, 2> newPos = tileMap[pos].move(pos, tileMap); //.move(pos) means: generate new position of tile based on the old position (argument) and tile type (Tile.name stored in struct)
                //tileMap[pos].say(pos);                      //EXAMPLE
                if (newPos != pos) //if moved: remove old pos from the map
                {
                    tileMap[newPos] = tileMap[pos];
                    tileMap.erase(pos);
                }
            }
            GrassUtils::grow(tileMap, grassPositions);
            // save data (per tick) to file

            data_file << lastTickTime << "," << Tile::get_grass_count() << "," << Tile::get_rabbit_count() << "," << Tile::get_fox_count() << std::endl;

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
    data_file.close();
    CloseWindow();
}