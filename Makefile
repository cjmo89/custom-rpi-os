CC = aarch64-linux-gnu
CFLAGS = -Wall -ffreestanding -nostdlib -nostartfiles -Iinclude -mgeneral-regs-only
BUILD_DIR = build
BOOT_DIR = /media/$$USER/boot

all: kernel8.img

$(BUILD_DIR)/%.o: %.S
	mkdir -p $(@D)
	$(CC)-gcc $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC)-gcc $(CFLAGS) -c $< -o $@

CFILES = $(wildcard *.c)
ASMFILES = $(wildcard *.S)
OFILES = $(CFILES:%.c=$(BUILD_DIR)/%.o)
OFILES += $(ASMFILES:%.S=$(BUILD_DIR)/%.o)

kernel8.img: link.ld $(OFILES)
	$(CC)-ld -nostdlib $(OFILES) -T link.ld -o $(BUILD_DIR)/kernel8.elf
	$(CC)-objcopy -O binary $(BUILD_DIR)/kernel8.elf kernel8.img
	cp kernel8.img $(BOOT_DIR)/
	cp config.txt $(BOOT_DIR)/

clean:
	rm -rf $(BUILD_DIR)
	rm -rf armstub/build
	rm kernel8.img
	rm armstub.bin

armstub/build/armstub.o: armstub/armstub.S
	mkdir -p $(@D)
	$(CC)-gcc $(CFLAGS) -c $< -o $@

armstub: armstub/build/armstub.o
	$(CC)-ld --section-start=.text=0 -o armstub/build/armstub.elf armstub/build/armstub.o
	$(CC)-objcopy armstub/build/armstub.elf -O binary armstub.bin
	cp armstub.bin $(BOOT_DIR)/
