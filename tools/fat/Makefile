CC=gcc
CFLAGS=-Iincludes -g
BUILD_DIR=../../build
FAT_BUILD_DIR=$(BUILD_DIR)/tools

.PHONY: all clean

all: $(FAT_BUILD_DIR)/fat

$(FAT_BUILD_DIR)/fat: always src/fat_main.c src/fat_utils.c includes/fat_structures.h includes/disk_operations.h
	mkdir -p $(FAT_BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ src/fat_main.c src/fat_utils.c

always:
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(FAT_BUILD_DIR)/fat