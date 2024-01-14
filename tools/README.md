
# FAT File System Reader

This utility reads from a FAT12 file system image and outputs the contents of the specified file.

## Overview

The FAT File System Reader is designed to work with FAT12 disk images. It handles reading the boot sector, file allocation table (FAT), and directory entries to locate and extract the content of files stored within the image.

## Building the Project

To compile the project, navigate to the root directory of the project and run:

```bash
make
```

This will compile all necessary components and produce an executable for the FAT tool.

## Usage

The tool is run from the command line as follows:

```bash
./fat_tool <disk_image_path> <file_name>
```

- `<disk_image_path>`: The path to the FAT12 disk image file.
- `<file_name>`: The name of the file to be read from the disk image.

## Program Structure

- `main`: The entry point for the program. It validates command line arguments, opens the disk image, and coordinates the reading process.
- `loadBootSector`: Reads the boot sector of the disk image to understand the file system structure.
- `loadFileAllocationTable`: Loads the FAT from the disk image, which is essential for file location and retrieval.
- `loadRootDirectory`: Loads the root directory entries to find the file of interest.
- `findDirectoryEntryByName`: Searches for the file within the root directory entries.
- `loadFileContents`: Reads the content of the file if it is found.

## Error Handling

The utility provides basic error handling, outputting errors to `stderr` and returning a non-zero status code if any problems occur during execution.

## Memory Management

All allocated memory is appropriately freed before the program exits to prevent memory leaks.

## Contributing

If you would like to contribute to this project, please:

1. Fork the repository.
2. Create a feature branch (`git checkout -b feature/fooBar`).
3. Commit your changes (`git commit -am 'Add some fooBar'`).
4. Push to the branch (`git push origin feature/fooBar`).
5. Open a new Pull Request.
