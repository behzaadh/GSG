# MATLAB Functions for GSG File Format (.gsg File)

## Overview

The MATLAB functions provides functionality to read and extract data from SLB Generic Simulation Grid (gsg) file format . These functions are designed to read and write various parameters from and to .gsg files, respectively. The primary objective is to facilitate the extraction and modification of Intersect restart file formats.

## Functions

### `read_gsg_all(filename)`

- Reads all parameters from a given .gsg file.
- Parameters are extracted and stored in a structured format.

#### Usage

```matlab
out = read_gsg_all('reservoir.gsg');
```

### `write_gsg_all(filename, out, fieldName)`

- Overwrites specified parameters in a .gsg file with new values.
- Multiple parameters can be modified simultaneously.

#### Usage

```matlab
input = ones(324,1)*100;
write_gsg_all('reservoir.gsg', input, ["TEMPERATURE"]);
```

### `write_gsg(filename, idx_start, data)`

- Internal function used by write_gsg_all.
- Writes data to a specific position in the .gsg file.

## Notes
- `write_gsg(filename, idx_start, data)`function is called by write_gsg_all.m and is not intended for standalone use.
-  Ensure the correct file paths are provided.

Feel free to contact me (bdhosseinzadeh@gmail.com) for any questions or assistance.
