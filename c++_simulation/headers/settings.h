#pragma once
///////////////////////////////////
// Standard Libraries
///////////////////////////////////
#include <array>
#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
///////////////////////////////////
// Headers
///////////////////////////////////



#include "raylib.h"
#include "global_enums.h"

///////////////////////////////////
// Settings
///////////////////////////////////
// Window
constexpr int screenWidth = 720;
constexpr int screenHeight = 720;
// Tick Speed
inline double tickDuration = 0.3;
// Grid
constexpr unsigned int gridSize = 60;
constexpr unsigned int cellSize = screenWidth / gridSize;
constexpr unsigned int gridLineThickness = 2;
inline Color gridLineColor = LIGHTGRAY;
// Tiles (Placeholder names)
constexpr unsigned int grassStartAmount = 10;
inline constexpr unsigned int grassMaxAmount = 50;
constexpr unsigned int rabbitStartAmount = 10;
constexpr unsigned int foxStartAmount = 10;
inline std::vector<unsigned int> tileStartAmounts{grassStartAmount, rabbitStartAmount, foxStartAmount};

inline void save_settings()
{
    std::fstream file;
    file.open("../data/Raw_Output.txt", std::ios::app);
    if (file.is_open())
    {
        // Not everything here needs to be saved, we can adjust later
        file << "Window size: "<< screenWidth << "x" << screenHeight << "px" << std::endl;
        file << "Tick duration: " << tickDuration << std::endl; //Seconds? Please add unit
        file << "Grid size: " << gridSize << "px" << std::endl;
        file << "Grid line thickness: " << gridLineThickness << "px" << std::endl;
        file << "Starting grass amount: " << grassStartAmount << std::endl;
        file << "Max grass amount: " << grassMaxAmount << std::endl;
        file << "Starting rabbit amount: " << rabbitStartAmount << std::endl;
        file << "Starting fox amount: " << foxStartAmount << std::endl;
    }
    file.close();
}

