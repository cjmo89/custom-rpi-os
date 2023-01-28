CC = aarch64-linux-gnu
CFLAGS = -Wall -ffreestanding -nostdlib -nostartfiles -mgeneral-regs-only
BUILD_DIR = build

all: kernel8.img

$(BUILD_DIR)/start.o: start.S
	mkdir -p $(@D)
	$(CC)-gcc $(CFLAGS) -c start.S -o $(BUILD_DIR)/start.o

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC)-gcc $(CFLAGS) -c $< -o $@

CFILES = $(wildcard *.c)
OFILES = $(CFILES:%.c=$(BUILD_DIR)/%.o)

kernel8.img: $(BUILD_DIR)/start.o $(OFILES)
	$(CC)-ld -nostdlib $(BUILD_DIR)/start.o $(OFILES) -T link.ld -o $(BUILD_DIR)/kernel8.elf
	$(CC)-objcopy -O binary $(BUILD_DIR)/kernel8.elf kernel8.img

clean:
	rm -rf $(BUILD_DIR) kernel8.img

run:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -d in_asm
