// Purpose: Read GSG file and extract data.
#include "GSGfile.h"
#include <memory>

std::string readKeyword(std::ifstream& file){
    // Read the size of the header
    int sizeHeader;
    file.read(reinterpret_cast<char*>(&sizeHeader), sizeof(int));

    // Read the keyword
    // char* keywordBuffer = new char[sizeHeader];
    std::unique_ptr<char[]> keywordBuffer(new char[sizeHeader]);
    file.read(keywordBuffer.get(), sizeHeader);
    std::string keyword(keywordBuffer.get(), sizeHeader);
    // delete[] keywordBuffer;

    // Remove whitespaces and replace '[' and ']' with '_'
    keyword.erase(std::remove_if(keyword.begin(), keyword.end(), ::isspace), keyword.end());
    std::replace(keyword.begin(), keyword.end(), '[', '_');
    std::replace(keyword.begin(), keyword.end(), ']', '_');

    return keyword;
}
int getStartIndex(std::ifstream& file) {
    // Set the starting position for reading the header (67 bytes)
    int idx_start = 67;
    file.seekg(idx_start, std::ios::beg);

    // Flag to check if the "PROP" keyword is found
    bool noProp = true;

    // Search for the "PROP" keyword in the header
    while (!file.eof()) {
        // Read the size of the header
        std::string keyword = readKeyword(file);

        if (keyword == "PROP") {
            // Adjust the starting position and set the flag to false
            idx_start = static_cast<int>(file.tellg()) - 8;
            noProp = false;
            break;
        } else if (keyword == "AXES") {
            file.seekg(72, std::ios::cur);
        } else if (keyword == "GRID") {
            file.seekg(8, std::ios::cur);
        } else if (keyword == "GRID_0") {
            file.seekg(44, std::ios::cur);
        }
    }

    return noProp ? -1 : idx_start;
}
// Function to read GSG file and extract data
GsgOutput readGsg(const std::string& filename) {
    // Open the file in binary mode
    std::ifstream file{filename, std::ios::binary};

    // Check if the file is open
    if (!file.is_open()) {
        // Throw an exception if the file cannot be opened
        throw std::runtime_error("Error: File does not exist or cannot be opened.");
    }

    int idx_start = getStartIndex(file);

    // Create the output structure
    GsgOutput out;

    // If "PROP" keyword is not found, display an error message and return empty output
    if (idx_start < 0) {
        std::cerr << "No properties in the file!" << std::endl;
        file.close();
        return out;
    }

    // Reset the file position to the adjusted starting position
    file.seekg(idx_start, std::ios::beg);

    // Read data from the GSG file
    while (!file.eof()) {
        // Read if it is properties or not
        std::string keyword = readKeyword(file);

        if (keyword == "CASE_PROPS") {
            std::cout << "All properties have been read successfully!" << std::endl;
            break;
        }

        // Skip the data
        file.seekg(8, std::ios::cur);

        // Read the properties keyword
        keyword = readKeyword(file);

        // Move to the data type and array size information
        file.seekg(4, std::ios::cur);

        // Read the data type
        int64_t type;
        file.read(reinterpret_cast<char*>(&type), sizeof(int64_t));

        // Read the array size
        int arraySize;
        file.read(reinterpret_cast<char*>(&arraySize), sizeof(int));

        // Create a GsgData structure to store the data
        GsgData data;

        // Read data based on the data type
        switch (type) {
            case 0:
                data.intData.resize(arraySize);
                if (!file.read(reinterpret_cast<char*>(data.intData.data()), arraySize * sizeof(int))) {
                    std::cerr << "Error reading array. Type: " << type << std::endl;
                    return out;
                }
                break;
            case 1:
                data.floatData.resize(arraySize);
                if (!file.read(reinterpret_cast<char*>(data.floatData.data()), arraySize * sizeof(float))) {
                    std::cerr << "Error reading array. Type: " << type << std::endl;
                    return out;
                }
                break;
            case 2:
                data.doubleData.resize(arraySize);
                if (!file.read(reinterpret_cast<char*>(data.doubleData.data()), arraySize * sizeof(double))) {
                    std::cerr << "Error reading array. Type: " << type << std::endl;
                    return out;
                }
                break;
            default:
                // Display an error message for an invalid data type
                std::cerr << "No valid type!" << std::endl;
                break;
        }

        // Store the keyword and data in the output structure
        out.headers.push_back(keyword);
        out.dataVector.push_back(data);
    }

    // Close the file
    file.close();

    // Return the populated output structure
    return out;
}

void writeGsg(const std::string& filename, const std::vector<std::string>& keywords, const GsgOutput& data) {
    // Open the file in binary mode
    std::ifstream file{filename, std::ios::binary};

    // Check if the file is open
    if (!file.is_open()) {
        // Throw an exception if the file cannot be opened
        throw std::runtime_error("Error: File does not exist or cannot be opened.");
    }

    // Set the starting position for reading the header (67 bytes)
    int idx_start = getStartIndex(file);

    // If "PROP" keyword is not found, display an error message and return empty output
    if (idx_start < 0) {
        std::cerr << "No properties in the file!" << std::endl;
        file.close();
        return;
    }

    // Reset the file position to the adjusted starting position
    file.seekg(idx_start, std::ios::beg);
    std::vector<std::streampos> startIdxVector;
    std::vector<int64_t> typeVector;

    // Read data from the GSG file
    while (!file.eof()) {
        // Read if it is properties or not
        std::string keyword = readKeyword(file);

        if (keyword == "CASE_PROPS") {
            break;
        }

        // Skip the data
        file.seekg(8, std::ios::cur);

        // Read the properties keyword
        keyword = readKeyword(file);

        bool found = false;
        int idx = 0;
        for (const std::string& key : keywords) {
            if (key == keyword) {
                found = true;
                std::cout << "Found " << keyword << std::endl;
                break; // Exit the loop once a match is found
            }
            idx++;
        }

        // Move to the data type and array size information
        file.seekg(4, std::ios::cur);

        // Read the data type
        int64_t type;
        file.read(reinterpret_cast<char*>(&type), sizeof(int64_t));

        // Read the array size
        int arraySize;
        file.read(reinterpret_cast<char*>(&arraySize), sizeof(int));

        // Read data based on the data type
        
        if (found) {
            startIdxVector.push_back(file.tellg());
            typeVector.push_back(type);
        }
        switch (type) {
            case 0:
                file.seekg(arraySize * sizeof(int), std::ios::cur);
                break;
            case 1:
                file.seekg(arraySize * sizeof(float), std::ios::cur);
                break;
            case 2:
                file.seekg(arraySize * sizeof(double), std::ios::cur);
                break;
            default:
                // Display an error message for an invalid data type
                std::cerr << "No valid type!" << std::endl;
                break;
        }
    }

    // Close the file
    file.close();

    for (size_t i = 0; i < startIdxVector.size(); i++)
    {
        writeGsg(filename, startIdxVector[i], typeVector[i], data.dataVector[i]);
    }
    
    std::cout << "Data has been written successfully!" << std::endl;
}

void writeGsg(const std::string& filename, std::streampos idx_start, int64_t type, const GsgData& data) {
    // Check if the filename is provided
    if (filename.empty()) {
        std::cerr << "Error: Filename is empty." << std::endl;
        return;
    }

    // Open the file in binary mode for reading and writing
    std::fstream file(filename, std::ios::binary | std::ios::in | std::ios::out);

    // Check if the file is open
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return;
    }

    // Set the file pointer to the specified starting index
    file.seekp(idx_start, std::ios::beg);

    switch (type) {
        case 0:
            file.write(reinterpret_cast<const char*>(data.intData.data()), data.intData.size() * sizeof(int));
            break;
        case 1:
            file.write(reinterpret_cast<const char*>(data.floatData.data()), data.floatData.size() * sizeof(float));
            break;
        case 2:
            file.write(reinterpret_cast<const char*>(data.doubleData.data()), data.doubleData.size() * sizeof(double));
            break;
        default:
            // Display an error message for an invalid data type
            std::cout << "No valid type!" << std::endl;
            break;
    }

    // Close the file
    file.close();
}
