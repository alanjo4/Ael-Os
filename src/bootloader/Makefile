ASM=nasm
BUILD_DIR=../../build

.PHONY: all clean

all: $(BUILD_DIR)/bootloader.bin

$(BUILD_DIR)/bootloader.bin: always boot.asm
	$(ASM) boot.asm -f bin -o $@

always:
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(BUILD_DIR)/bootloader.bin