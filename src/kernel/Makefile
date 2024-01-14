ASM=nasm
BUILD_DIR=../../build

.PHONY: all clean

all: $(BUILD_DIR)/kernel.bin

$(BUILD_DIR)/kernel.bin: always main.asm
	$(ASM) main.asm -f bin -o $@

always:
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(BUILD_DIR)/kernel.bin