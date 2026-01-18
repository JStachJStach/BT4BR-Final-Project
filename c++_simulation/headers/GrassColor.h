#pragma once
#include "settings.h"
#include "map"
struct GrassColor
{
    GrassColor()
    {
       colors = {
            {10, {0x77, 0xF7, 0x6C, 0xFF}},  // #77f76c
            {9, {0x81, 0xF8, 0x76, 0xFF}},  // #81f876
            {8, {0x8D, 0xF9, 0x83, 0xFF}},  // #8df983
            {7, {0x99, 0xF9, 0x91, 0xFF}},  // #99f991
            {6, {0xA7, 0xFA, 0xA0, 0xFF}},  // #a7faa0
            {5, {0xB6, 0xFB, 0xB0, 0xFF}},  // #b6fbb0
            {4, {0xC4, 0xFC, 0xBF, 0xFF}},  // #c4fcbf
            {3, {0xD2, 0xFC, 0xCE, 0xFF}},  // #d2fcce
            {2, {0xE1, 0xFD, 0xDE, 0xFF}},  // #e1fdde
            {1, {0xF1, 0xFE, 0xF0, 0xFF}},  // #f1fef0
            {0, {0xF5, 0xF5, 0xF5, 0xFF}},  // #f1fef0
        };
    }
    std::map<int, Color> colors;
    Color calculateGrassColor(const int &grassLevel) const
    {
        try
        {
            return colors.at(grassLevel/10);
        }
        catch (...)
        {
            return colors.at(10);
        }
    }
};