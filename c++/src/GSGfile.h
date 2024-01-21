#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

struct GsgData {
    std::vector<int> intData;
    std::vector<float> floatData;
    std::vector<double> doubleData;
    std::vector<std::string> stringData;
};

struct GsgOutput {
    std::vector<std::string> headers;
    std::vector<GsgData> dataVector;
};

/**
 * Reads a keyword from the given input file stream.
 *
 * @param file The input file stream to read from.
 * @return The keyword read from the file.
 */
std::string readKeyword(std::ifstream& file);
/**
 * Retrieves the start index of the file by skipping headers.
 *
 * @param file The input file stream.
 * @return The start index of the file.
 */
int getStartIndex(std::ifstream& file);
/**
 * Reads all data from a GSG file.
 *
 * @param filename The path to the GSG file.
 * @return The GsgOutput object containing the data read from the file.
 */
GsgOutput readGsgAll(const std::string& filename);
/**
 * Writes GSG data to a file.
 *
 * @param filename The name of the file to write the data to.
 * @param keywords The list of keywords associated with the data to be written.
 * @param data The GsgOutput data to write.
 */
void writeGsg(const std::string& filename, const std::vector<std::string>& keywords, const GsgOutput& data);

/**
 * Overwrites GSG data to a file only for one keyword.
 *
 * @param filename The name of the file to write the GSG data to.
 * @param idx_start The starting position in the file where the GSG data should be written.
 * @param type The type of GSG data.
 * @param data The GSG data to be written.
 */
void writeGsg(const std::string& filename, std::streampos idx_start, int64_t type, const GsgData& data);