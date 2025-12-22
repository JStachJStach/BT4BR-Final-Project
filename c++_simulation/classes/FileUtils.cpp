#include "../headers/FileUtils.h"
void FileUtils::saveCSV(const std::vector<FileUtils>& data)
{
    std::fstream data_file;
    data_file.open("../data/raw/data.csv", std::ios::out | std::ios::trunc);
    if (data_file.is_open())
    {
        data_file << "lastTickTime" << "," << "Tile::grass_count" << "," << "Tile::rabbit_count" << "," << "Tile::fox_count" << std::endl;
        for (const auto & i : data)
        {
            data_file << i.lastTickTime << "," << i.grassCount << "," << i.rabbitCount << "," << i.foxCount<< std::endl;
        }
        data_file.close();
    }

}
