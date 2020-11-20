NASM := /bin/nasm
LD := /bin/ld
GRUB_MKRESCUE := /bin/grub-mkrescue
QEMU_SYSTEM_I386 := /bin/qemu-system-i386
GCC := /bin/gcc

ISO_DIR := iso
OUTPUT := build/kernel.elf
ISO_OS_OUTPUT := $(ISO_DIR)/boot/lukeos.bin
ISO_OUTPUT_FILE := build/lukeos.iso

OBJECTS := kernel.o boot.o modules/graphics/framebuffer.o modules/io.o modules/serial/serial.o

# Prepares the NASM args
NASM_ARGS += -f elf32

# Prepares the GCC args
GCC_ARGS += -Wall -Wextra
GCC_ARGS += -Os
GCC_ARGS += -m32
GCC_ARGS += -nostdlib -nostdinc -fno-stack-protector -nostartfiles -nodefaultlibs
GCC_ARGS += -fno-exceptions

# Prepares the linker flags
LD_ARGS += -T linker.ld
LD_ARGS += -m elf_i386

# The rules
prepare:
	mkdir -p build
all: prepare $(OBJECTS)
	$(LD) $(LD_ARGS) $(OBJECTS) -o $(OUTPUT)
iso: all
	mv $(OUTPUT) $(ISO_OS_OUTPUT)
	$(GRUB_MKRESCUE) $(ISO_DIR) -o $(ISO_OUTPUT_FILE)
emulate: iso
	$(QEMU_SYSTEM_I386) $(ISO_OUTPUT_FILE) -smp 2
clean:
	rm -rf $(OBJECTS) $(ISO_OUTPUT_FILE) $(OUTPUT)

# Compiles all source files
%.o: %.cc
	$(GCC) -c $(GCC_ARGS) $< -o $@
%.o: %.s
	$(NASM) $(NASM_ARGS) $< -o $@