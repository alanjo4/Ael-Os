#ifndef DISK_OPERATIONS_H
#define DISK_OPERATIONS_H

#include "fat_structures.h"
#include <stdio.h>

bool loadBootSector(FILE *disk);
bool readDiskSectors(FILE *disk, uint32_t sectorNumber, uint32_t sectorCount, void *destination);
bool loadFileAllocationTable(FILE *disk);
bool loadRootDirectory(FILE *disk);
DirectoryEntry *findDirectoryEntryByName(const char *fileName);
bool loadFileContents(DirectoryEntry *file, FILE *disk, uint8_t *outputBuffer);

#endif
