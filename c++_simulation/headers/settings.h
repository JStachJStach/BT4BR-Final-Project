#pragma once
///////////////////////////////////
// Standard Libraries
///////////////////////////////////
#include <array>
#include <map>
#include <iostream>
#include <string>

///////////////////////////////////
// Headers
///////////////////////////////////

#include "raylib.h"
#include "global_enums.h"

///////////////////////////////////
// Settings
///////////////////////////////////
constexpr int screenWidth = 720;
constexpr int screenHeight = 720;
inline double tickDuration = 0.3;
// Grid
constexpr unsigned int gridSize = 60;
constexpr unsigned int cellSize = screenWidth / gridSize;
constexpr unsigned int gridLineThickness = 2;
inline Color gridLineColor = LIGHTGRAY;
