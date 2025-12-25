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




#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include "raylib.h"
#include "global_enums.h"

///////////////////////////////////
// Settings
///////////////////////////////////

// Window
inline unsigned int screenWidth;
inline unsigned int screenHeight;

// Tick Speed
inline double tickDuration ;

// Grid
inline unsigned int gridSize;
inline unsigned int cellSize;
inline unsigned int gridLineThickness;
constexpr Color gridLineColor = LIGHTGRAY; // This has to stay here unless we want to deal with overloading the json hpp somehow

// Tiles
inline unsigned int grassMaxAmount;
inline float grassGrowChance;
inline std::vector<unsigned int> tileStartAmounts{};

// Reproduction and death
inline int rabbitMaxSat;
inline int rabbitMinSat;
inline int rabbitReproductionSat;
inline int rabbitSatPerGrass;
inline int rabbitSatPerTick;

inline int foxMaxSat;
inline int foxMinSat;
inline int foxReproductionSat;
inline int foxSatPerRabbit;
inline int foxSatPerTick;

inline void get_settings()
{
    const std::string settingsFilePath = "settings.json";
    std::ifstream file(settingsFilePath);
    if (file.is_open())
    {
        json settings = json::parse(file);
        // Window size
        screenWidth = settings.at("window").value("width", 720u);
        screenHeight = settings.at("window").value("height", 720u);

        // Tick
        tickDuration = settings.at("tick").value("duration", 0.05);

        // Grid
        gridSize = settings.at("grid").value("size", 120u);
        gridLineThickness = settings.at("grid").value("lineThickness", 2u);
        cellSize = screenHeight / gridSize;
        // Tile start amounts
        for(const auto& name : settings.at("tiles").at("startOrder"))
        {
            tileStartAmounts.push_back(
                settings.at("tiles")
                .at("definitions")
                .at(name.get<std::string>())
                .at("startAmount")
                .get<unsigned int>()
                );
        }
        // Grass
        grassGrowChance = settings.at("tiles").at("definitions").at("grass").value("growChance", 0.75f);
        grassMaxAmount = settings.at("tiles").at("definitions").at("grass").value("maxAmount", 1000);

        // Rabbits
        rabbitMaxSat = settings.at("animals").at("rabbit").value("maxSat", 75);
        rabbitMinSat = settings.at("animals").at("rabbit").value("minSat", -50);
        rabbitReproductionSat = settings.at("animals").at("rabbit").value("reproductionSat", 73);
        rabbitSatPerGrass = settings.at("animals").at("rabbit").value("satPerFood", 25);
        rabbitSatPerTick = settings.at("animals").at("rabbit").value("satPerTick", -1);

        // Foxes
        foxMaxSat = settings.at("animals").at("fox").value("maxSat", 75);
        foxMinSat = settings.at("animals").at("fox").value("minSat", -50);
        foxReproductionSat = settings.at("animals").at("fox").value("reproductionSat", 73);
        foxSatPerRabbit = settings.at("animals").at("fox").value("satPerFood", 25);
        foxSatPerTick = settings.at("animals").at("fox").value("satPerTick", -1);
    }
    else
    {
        throw std::runtime_error("Could not open " + settingsFilePath);
    }
}



inline void save_settings()
{
    // Open file for saving settings in append mode
    const std::string path = "../data/settings_used.txt";
    std::ofstream file;
    file.open(path, std::ios::app);

    // Check if file has opened correctly
    if (file.is_open())
    {
        // Not everything here needs to be saved, we can adjust later
        file << "Settings used: " << std::endl;
        file << "Window size: "<< screenWidth << "x" << screenHeight << "px" << std::endl;
        file << "Tick duration: " << tickDuration << std::endl; //Seconds? Please add unit
        file << std::endl;
        file << "Grid: " << std::endl;
        file << "Grid size: " << gridSize << "px" << std::endl;
        file << "Grid line thickness: " << gridLineThickness << "px" << std::endl;
        file << std::endl;
        file << "Grass parameters: " << std::endl;
        file << "Starting grass amount: " << tileStartAmounts[static_cast<int>(TileState::Grass)] << std::endl;
        file << "Max grass amount: " << grassMaxAmount << std::endl;
        file << std::endl;
        file << "Rabbit parameters: " << std::endl;
        file << "Starting rabbit amount: " << tileStartAmounts[static_cast<int>(TileState::Rabbit)] << std::endl;
        file << "Maximum rabbit saturation: " << rabbitMaxSat << std::endl;
        file << "Minimum rabbit saturation: " << rabbitMinSat << std::endl;
        file << "Rabbit reproduction saturation: " << rabbitReproductionSat << std::endl;
        file << "Rabbit saturation per meal: " << rabbitSatPerGrass << std::endl;
        file << "Rabbit hunger rate per tick: " << rabbitSatPerTick << std::endl;
        file << std::endl;
        file << "Fox parameters: " << std::endl;
        file << "Starting fox amount: " << tileStartAmounts[static_cast<int>(TileState::Fox)] << std::endl;
        file << "Maximum fox saturation: " << foxMaxSat << std::endl;
        file << "Minimum fox saturation: " << foxMinSat << std::endl;
        file << "Fox reproduction saturation: " << foxReproductionSat << std::endl;
        file << "Fox saturation per meal: " << foxSatPerRabbit << std::endl;
        file << "Fox hunger rate per tick: " << foxSatPerTick << std::endl;
        file.close();
    }
    else
    {
        throw std::runtime_error("Could not open file " + path);
    }

}

