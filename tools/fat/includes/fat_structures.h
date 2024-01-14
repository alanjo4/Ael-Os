#ifndef FAT_STRUCTURES_H
#define FAT_STRUCTURES_H

#include <stdint.h>
#include <stdbool.h>

#define true 1
#define false 0

// Please notice that the following structures are packed, which means that the compiler will not add any padding bytes between the fields.
/*
And also please notice that you are not able to use long filenames
because the FAT32 filesystem does not support them. We are using
8.3 filenames, which means that the filename is 8 characters long and the extension is 3 characters long.
We can implement VFAT (Virtual File Allocation Table) support later.
*/


typedef struct {
    uint8_t BootJumpInstruction[3];
    uint8_t OemIdentifier[8];
    uint16_t BytesPerSector;
    uint8_t SectorsPerCluster;
    uint16_t ReservedSectors;
    uint8_t FatCount;
    uint16_t DirEntryCount;
    uint16_t TotalSectors;
    uint8_t MediaDescriptorType;
    uint16_t SectorsPerFat;
    uint16_t SectorsPerTrack;
    uint16_t Heads;
    uint32_t HiddenSectors;
    uint32_t LargeSectorCount;
    uint8_t DriveNumber;
    uint8_t Reserved;
    uint8_t Signature;
    uint32_t VolumeId;
    uint8_t VolumeLabel[11];
    uint8_t SystemId[8];
} __attribute__((packed)) BootSector;

typedef struct {
    uint8_t Name[11];
    uint8_t Attributes;
    uint8_t Reserved;
    uint8_t CreatedTimeTenths;
    uint16_t CreatedTime;
    uint16_t CreatedDate;
    uint16_t AccessedDate;
    uint16_t FirstClusterHigh;
    uint16_t ModifiedTime;
    uint16_t ModifiedDate;
    uint16_t FirstClusterLow;
    uint32_t Size;
} __attribute__((packed)) DirectoryEntry;

extern BootSector bootSector;
extern uint8_t *fileAllocationTable;
extern DirectoryEntry *rootDirectoryEntries;
extern uint32_t rootDirectoryEndSector;

#endif // FAT_STRUCTURES_H
