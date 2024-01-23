# GSG File Reader/Writer (.gsg File)

## Overview

This C++ code provides functionality to read and extract data from SLB Generic Simulation Grid (gsg) file format . These functions are designed to read and write various parameters from and to .gsg files, respectively. The primary objective is to facilitate the extraction and modification of Intersect restart file formats.


## File Structure

- **GSGfile.h:** Header file containing declarations for functions and data structures.
- **main.cpp:** Test file showcasing the usage of the GSG file reader and writer.

## GSGfile.h

### Functions

1. **`readKeyword(std::ifstream& file)`**

   - Reads the size of the header and the keyword from the GSG file.
   - Cleans up the keyword by removing whitespaces and replacing '[' and ']' with '_'.
   - Returns the cleaned keyword.

2. **`getStartIndex(std::ifstream& file)`**

   - Searches for the "PROP" keyword in the GSG file header.
   - Determines the starting position for reading the GSG file.
   - Returns the starting index or -1 if "PROP" is not found.

3. **`readGsg(const std::string& filename)`**

   - Reads the GSG file, extracts data, and stores it in a structured format (`GsgOutput`).
   - Handles different data types and array sizes.
   - Returns the populated `GsgOutput` structure.

4. **`writeGsg(const std::string& filename, const std::vector<std::string>& keywords, const GsgOutput& data)`**

   - Overwrites specified parameters in the GSG file with new values.
   - Takes a vector of keywords, a `GsgOutput` structure containing new data, and the GSG file's filename.
   - Modifies the file in-place.

5. **`writeGsg(const std::string& filename, std::streampos idx_start, int64_t type, const GsgData& data)`**

   - Internal function used by `writeGsg` to write data at a specific position in the GSG file.
   - Utilizes the file's starting position (`idx_start`), data type (`type`), and data (`GsgData`).

## main.cpp (Test File)

- Demonstrates the usage of the GSG file reader and writer functions.
- Reads, modifies, and writes GSG files.
- Provides test cases to showcase the functionality.

## Notes

- `writeGsg(const std::string& filename, std::streampos idx_start, int64_t type, const GsgData& data)`function is called by `writeGsg(const std::string& filename, const std::vector<std::string>& keywords, const GsgOutput& data)` function and is not intended for standalone use.
- Ensure the GSG file path is correctly provided.

Feel free to contact me (behzadh@dtu.dk) for any questions or assistance.
