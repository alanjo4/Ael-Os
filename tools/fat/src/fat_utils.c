#include "../includes/fat_structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern BootSector bootSector;
extern uint8_t *fileAllocationTable;
extern DirectoryEntry *rootDirectoryEntries;
extern uint32_t rootDirectoryEndSector;

bool loadBootSector(FILE *disk)
{
	return fread(&bootSector, sizeof(bootSector), 1, disk) > 0;
}

bool readDiskSectors(FILE *disk, uint32_t sectorNumber, uint32_t sectorCount, void *destination)
{
	bool success = true;
	success = success && (fseek(disk, sectorNumber * bootSector.BytesPerSector, SEEK_SET) == 0);
	success = success && (fread(destination, bootSector.BytesPerSector, sectorCount, disk) == sectorCount);
	return success;
}

bool loadFileAllocationTable(FILE *disk)
{
	fileAllocationTable = (uint8_t *)malloc(bootSector.SectorsPerFat * bootSector.BytesPerSector);
	return readDiskSectors(disk, bootSector.ReservedSectors, bootSector.SectorsPerFat, fileAllocationTable);
}

bool loadRootDirectory(FILE *disk)
{
	uint32_t sectorNumber = bootSector.ReservedSectors + bootSector.SectorsPerFat * bootSector.FatCount;
	uint32_t directorySize = sizeof(DirectoryEntry) * bootSector.DirEntryCount;
	uint32_t sectorCount = (directorySize / bootSector.BytesPerSector);
	if (directorySize % bootSector.BytesPerSector > 0)
	{
		sectorCount++;
	}
	rootDirectoryEndSector = sectorNumber + sectorCount;
	rootDirectoryEntries = (DirectoryEntry *)malloc(sectorCount * bootSector.BytesPerSector);
	return readDiskSectors(disk, sectorNumber, sectorCount, rootDirectoryEntries);
}

DirectoryEntry *findDirectoryEntryByName(const char *fileName)
{

	for (uint32_t i = 0; i < bootSector.DirEntryCount; i++)
	{
		printf("Entry %d: %s\n", i, rootDirectoryEntries[i].Name);
		if (memcmp(fileName, rootDirectoryEntries[i].Name, 11) == 0)
			return &rootDirectoryEntries[i];
	}
	return NULL;
}

bool loadFileContents(DirectoryEntry *file, FILE *disk, uint8_t *outputBuffer)
{
	bool success = true;
	uint16_t currentCluster = file->FirstClusterLow;

	do
	{
		uint32_t sectorNumber = rootDirectoryEndSector + (currentCluster - 2) * bootSector.SectorsPerCluster;
		success = success && readDiskSectors(disk, sectorNumber, bootSector.SectorsPerCluster, outputBuffer);
		outputBuffer += bootSector.SectorsPerCluster * bootSector.BytesPerSector;

		uint32_t fatIndex = currentCluster * 3 / 2;
		if (currentCluster % 2 == 0)
			currentCluster = (*(uint16_t *)(fileAllocationTable + fatIndex)) & 0x0FFF;
		else
			currentCluster = (*(uint16_t *)(fileAllocationTable + fatIndex)) >> 4;

	} while (success && currentCluster < 0x0FF8);

	return success;
}