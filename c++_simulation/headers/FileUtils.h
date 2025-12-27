#pragma once
#include "settings.h"
struct FileUtils
{
    double lastTickTime;
    int grassCount;
    int rabbitCount;
    int foxCount;

    static void saveCSV(const std::vector<FileUtils>& dataVector);
    private:
    static bool hasOpenedThisCycle;
};