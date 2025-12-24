#include "../headers/FileUtils.h"
/**
 * Static method to save collected tile data into CSV format
 * @param dataVector Vector containing collected tile data
 */
void FileUtils::saveCSV(const std::vector<FileUtils>& dataVector)
{
    // Open file in write mode wherein the data is saved
    std::ofstream data_file;
    const std::string filePath = "../data/raw/data.csv";
    data_file.open(filePath);

    // Check if the file has opened correctly
    if (data_file.is_open())
    {
        // Save variable names for CSV columns
        data_file << "lastTickTime" << "," << "Tile::grassCount" << "," << "Tile::rabbitCount" << "," << "Tile::foxCount" << std::endl;

        // Loop over the vector containing the collected data
        for (const auto & i : dataVector)
        {
            // Save data delimited by ','
            data_file << i.lastTickTime << "," << i.grassCount << "," << i.rabbitCount << "," << i.foxCount<< std::endl;
        }
        // Close the file
        data_file.close();
    }
    else
    {
        throw std::runtime_error("Could not open file" + std::string(filePath));
    }
}
