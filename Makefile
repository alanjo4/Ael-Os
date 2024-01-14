ASM=nasm
CC=gcc
BUILD_DIR=build
SRC_DIR=src

.PHONY: all floppy_image kernel bootloader clean always tools_fat

all: floppy_image tools_fat

floppy_image: $(BUILD_DIR)/main_floppy.img

$(BUILD_DIR)/main_floppy.img: bootloader kernel
	dd if=/dev/zero of=$(BUILD_DIR)/main_floppy.img bs=512 count=2880
	mkfs.fat -F 12 -n "NBOS" $(BUILD_DIR)/main_floppy.img
	dd if=$(BUILD_DIR)/bootloader.bin of=$(BUILD_DIR)/main_floppy.img conv=notrunc
	mcopy -i $(BUILD_DIR)/main_floppy.img $(BUILD_DIR)/kernel.bin "::kernel.bin"
	mcopy -i $(BUILD_DIR)/main_floppy.img test.txt "::test.txt"

bootloader:
	$(MAKE) -C $(SRC_DIR)/bootloader

kernel:
	$(MAKE) -C $(SRC_DIR)/kernel

tools_fat:
	$(MAKE) -C tools/fat

clean:
	$(MAKE) -C $(SRC_DIR)/bootloader clean
	$(MAKE) -C $(SRC_DIR)/kernel clean
	$(MAKE) -C $(SRC_DIR)/tools/fat clean

always:
	mkdir -p ${BUILD_DIR}