#include <stdio.h>
#include <string.h>
#include <ctype.h>

void convertToFatFormat(const char* inputName, char* fatName) {
    int nameLength = 0;
    int extLength = 0;
    const char* ext = strchr(inputName, '.');

    if (ext != NULL) {
        nameLength = ext - inputName;
        ext++;
        extLength = strlen(ext);
    } else {
        nameLength = strlen(inputName);
    }

    for (int i = 0; i < 8; i++) {
        if (i < nameLength) {
            fatName[i] = toupper(inputName[i]);
        } else {
            fatName[i] = ' ';
        }
    }

    for (int i = 0; i < 3; i++) {
        if (ext != NULL && i < extLength) {
            fatName[i + 8] = toupper(ext[i]);
        } else {
            fatName[i + 8] = ' ';
        }
    }

    fatName[11] = '\0';
}

int main() {
    char fatName[12];
    convertToFatFormat("test.txt", fatName);
    printf("Nombre en formato FAT: %s\n", fatName);

    convertToFatFormat("example.txt", fatName);
    printf("Nombre en formato FAT: %s\n", fatName);

    return 0;
}