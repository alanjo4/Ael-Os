#include "../includes/fat_structures.h"
#include "../includes/disk_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

BootSector bootSector;
uint8_t *fileAllocationTable = NULL;
DirectoryEntry *rootDirectoryEntries = NULL;
uint32_t rootDirectoryEndSector;

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Syntax: %s <disk image> <file name>\n", argv[0]);
        return -1;
    }

    FILE *disk = fopen(argv[1], "rb");
    if (!disk) {
        fprintf(stderr, "Cannot open disk image %s!\n", argv[1]);
        return -1;
    }

    if (!loadBootSector(disk)) {
        fprintf(stderr, "Could not read boot sector!\n");
        return -2;
    }

    if (!loadFileAllocationTable(disk)) {
        fprintf(stderr, "Could not read FAT!\n");
        free(fileAllocationTable);
        return -3;
    }

    if (!loadRootDirectory(disk)) {
        fprintf(stderr, "Could not read root directory!\n");
        free(fileAllocationTable);
        free(rootDirectoryEntries);
        return -4;
    }

    DirectoryEntry *fileEntry = findDirectoryEntryByName(argv[2]);
    if (!fileEntry) {
        fprintf(stderr, "Could not find file %s!\n", argv[2]);
        free(fileAllocationTable);
        free(rootDirectoryEntries);
        return -5;
    }

    uint8_t *buffer = (uint8_t *)malloc(fileEntry->Size + bootSector.BytesPerSector);
    if (!loadFileContents(fileEntry, disk, buffer)) {
        fprintf(stderr, "Could not read file %s!\n", argv[2]);
        free(fileAllocationTable);
        free(rootDirectoryEntries);
        free(buffer);
        return -6;
    }

    for (size_t i = 0; i < fileEntry->Size; i++) {
        if (isprint(buffer[i]))
            fputc(buffer[i], stdout);
        else
            printf("<%02x>", buffer[i]);
    }
    printf("\n");

    free(buffer);
    free(fileAllocationTable);
    free(rootDirectoryEntries);
    fclose(disk);
    return 0;
}