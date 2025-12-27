#include <ranges>


#include "headers/GrassUtils.h"
#include "headers/settings.h"
#include "headers/RandomUtils.h"
#include "headers/global_enums.h"
#include "headers/Tile.h"
#include "headers/FileUtils.h"

//TODO
//Bug: Grass is growing beyond borders (Done?)
//Modified Grass behavior (Done?)
//Fix get_random_tile allowing for duplicates



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
    try
    {
        RandomUtils::save_seed();
        get_settings();
        save_settings();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }




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
        for (int j = 0; j < tileStartAmounts[i]; j++)
        {
            RandomUtils::get_random_tile(tileMap, state);
        }
    }
    double lastTickTime = 0; //this is necessary to perform tick update (look at the statement ( if (lastTickTime + tickDuration < GetTime()) ) )
    InitWindow(screenWidth, screenHeight, "Simulation");
    SetTargetFPS(60);

    // FileUtils object because file I/O operations are a lot slower than memory I/O operations
    FileUtils FileUtil{};
    // Save data to a vector
    std::vector<FileUtils> overTimeData;

    std::vector<std::array<int, 2>> tilesPositions; // tilesPosition is made to make the choice of position unbiased (e.g. not from left to right)
    std::vector<std::array<int, 2>> grassPositions; // separate Array for grass since it shouldn't move

    unsigned int cycleCounter = 0;
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
                std::array<int, 2> newPos = tileMap[pos].act(pos, tileMap); //.act(pos,tileMap) is responsible for status and behavior
                if (newPos != pos) //if moved: remove old pos from the map
                {
                    tileMap[newPos] = tileMap[pos];
                    tileMap.erase(pos);
                }
            }
            GrassUtils::grow(tileMap, grassPositions);
            cycleCounter++;
            // save data (per tick) to vector
            FileUtil.lastTickTime = lastTickTime;
            FileUtil.grassCount = Tile::get_grass_count();
            FileUtil.rabbitCount = Tile::get_rabbit_count();
            FileUtil.foxCount = Tile::get_fox_count();
            overTimeData.push_back(FileUtil);
            if (cycleCounter % ticksPerSave == 0)
            {
                FileUtils::update(overTimeData);
            }
            lastTickTime = GetTime(); //look at the statement ( if (lastTickTime + tickDuration < GetTime()) )

            // If there are no animals left, close the window. We don't need to check grass as if there's no bunnies left it will have grown by the time
            // the foxes die and if there are no foxes left the bunnies are going to eat it all
            if (!Tile::get_rabbit_count() && !Tile::get_fox_count())
            {
               break;
            }
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

    try
    {
        FileUtils::saveCSV(overTimeData);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    CloseWindow();
}