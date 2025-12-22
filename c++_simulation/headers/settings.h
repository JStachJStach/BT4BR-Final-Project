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
// Window//
constexpr int screenWidth = 720;
constexpr int screenHeight = 720;
// Tick Speed
inline double tickDuration = 0.05;
// Grid
constexpr unsigned int gridSize = 100;
constexpr unsigned int cellSize = screenWidth / gridSize;
constexpr unsigned int gridLineThickness = 2;
inline Color gridLineColor = LIGHTGRAY;
// Tiles (Placeholder names)
constexpr unsigned int grassStartAmount = 10;
inline constexpr unsigned int grassMaxAmount = 1000;
constexpr unsigned int rabbitStartAmount = 30;
constexpr unsigned int foxStartAmount = 10;
inline std::vector<unsigned int> tileStartAmounts{grassStartAmount, rabbitStartAmount, foxStartAmount};
//Reproduction and death
constexpr int rabbitMaxSat = 75;
constexpr int rabbitMinSat = -50;
constexpr int rabbitReproductionSat = 73;
constexpr int rabbitSatPerGrass = 25;
constexpr int rabbitSatPerTick = -1;

constexpr int foxMaxSat = 75;
constexpr int foxMinSat = -50;
constexpr int foxReproductionSat = 73;
constexpr int foxSatPerRabbit = 25;
constexpr int foxSatPerTick = -1;


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

