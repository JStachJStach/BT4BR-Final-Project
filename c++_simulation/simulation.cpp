#include <ranges>


#include "headers/settings.h"
#include "headers/RandomUtils.h"
#include "headers/global_enums.h"
#include "headers/FileUtils.h"
#include "headers/TileMap.h"
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

void DrawTiles(Grid &grid) //this function calls draw methods of all tiles in tilemap
{
    std::vector<Position> occupied = grid.get_occupied();

    for (Position pos : occupied) {
        if (auto tile = grid.get(pos)) {
            tile->draw(pos);
        }
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
    TileMap tileMap;

    double lastTickTime = 0; //this is necessary to perform tick update (look at the statement ( if (lastTickTime + tickDuration < GetTime()) ) )
    InitWindow(screenWidth, screenHeight, "Simulation");
    SetTargetFPS(60);

    // FileUtils object because file I/O operations are a lot slower than memory I/O operations
    FileUtils FileUtil{};
    // Save data to a vector
    std::vector<FileUtils> overTimeData;

    std::vector<Position> tilesPositions; // tilesPosition is made to make the choice of position unbiased (e.g. not from left to right)

    unsigned int cycleCounter = 0;
    while (!WindowShouldClose())
    {
        ///////////////////////////////////
        // Update per tick
        ///////////////////////////////////

        if (lastTickTime + tickDuration < GetTime()) //this condition is fulfilled only once per tickDuration
        {
            tileMap.tick();

            cycleCounter++;
            // save data (per tick) to vector
            FileUtil.lastTickTime = lastTickTime;
            FileUtil.rabbitCount = tileMap.get_rabbit_count();
            FileUtil.foxCount = tileMap.get_fox_count();
            overTimeData.push_back(FileUtil);
            if (cycleCounter % ticksPerSave == 0)
            {
                FileUtils::saveCSV(overTimeData);
            }
            lastTickTime = GetTime(); //look at the statement ( if (lastTickTime + tickDuration < GetTime()) )

            // If there are no animals left, close the window. We don't need to check grass as if there's no bunnies left it will have grown by the time
            // the foxes die and if there are no foxes left the bunnies are going to eat it all

        }

        ///////////////////////////////////
        // Draw
        ///////////////////////////////////
        BeginDrawing();
        DrawGrid();
        DrawTiles(tileMap.get_tile_grid());
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