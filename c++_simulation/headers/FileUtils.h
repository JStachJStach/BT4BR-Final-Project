#pragma once
#include "settings.h"
struct FileUtils
{
    double lastTickTime;
    int grassCount;
    int rabbitCount;
    int foxCount;

    static void saveCSV(const std::vector<FileUtils>& dataVector);
    static void saveCSV(const std::vector<float>& dataVector);
	static void prepareCSV();
	static void clearCSV();
    //static void saveFrame(const std::vector<FileUtils>& dataVector);
    private:
    static bool hasOpenedThisCycle;
};