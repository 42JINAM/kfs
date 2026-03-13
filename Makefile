# ==============================
# Compiler & Tools
# ==============================

# AS     := i686-elf-as
AS      := nasm
CC      := i686-elf-gcc
LD      := i686-elf-gcc

# ==============================
# Directories
# ==============================

SRCDIR  := src
OBJDIR  := objs
OUTDIR  := output

# ==============================
# Files
# ==============================

NAME    := kfs-1
KERNEL  := $(NAME).bin
IMAGE   := $(NAME).iso

CFILES  := kernel terminal vga keyboard init switch_tab \
		   utils/memcpy \
		   utils/memset \
		   utils/strlen \
		   utils/printf \
		   utils/printf_format \
		   ascii/ascii_1_bonus \
		   ascii/ascii_2_bonus \
		   ascii/ascii_3_bonus \
		   ascii/ascii_4_bonus \
		   ascii/ascii_5_bonus \
		   ascii/ascii_bonus
SFILES  := boot

C_OBJS  := $(addprefix $(OBJDIR)/, $(addsuffix .o, $(CFILES)))
S_OBJS  := $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SFILES)))
OBJS    := $(C_OBJS) $(S_OBJS)

# ==============================
# Colors
# ==============================

CGREEN  := \033[32m
CYELLOW := \033[33m
CEND    := \033[0m

# ==============================
# Default Target
# ==============================

all: $(IMAGE)

# ==============================
# Build Rules
# ==============================

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostdlib -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.s | $(OBJDIR)
	$(AS) -f elf $< -o $@

$(KERNEL): $(OBJS) linker.ld
	$(LD) -nostdlib -ffreestanding -O2 -T linker.ld -o $@ $(OBJS) -lgcc
	@echo "$(CGREEN)[✓] $(KERNEL) created$(CEND)"

$(IMAGE): $(KERNEL) grub.cfg
	@echo "$(CYELLOW)[*] Creating ISO image...$(CEND)"
	rm -rf $(OUTDIR)
	mkdir -p $(OUTDIR)
	docker compose up --build
	cp $(OUTDIR)/$(IMAGE) .
	@echo "$(CGREEN)[✓] $(IMAGE) created$(CEND)"

# ==============================
# Convenience Targets
# ==============================
build: $(IMAGE)
	@echo "$(CGREEN)[✓] Build finished$(CEND)"

run: $(IMAGE)
	@echo "$(CYELLOW)[*] Running $(IMAGE) in QEMU...$(CEND)"
	qemu-system-i386 -cdrom $(IMAGE)

# debug: $(IMAGE)
# 	@echo "$(CYELLOW)[*] Running $(IMAGE) in QEMU in debug mode...$(CEND)"
# 	qemu-system-i386 -s -S -cdrom $(IMAGE)

clean:
	rm -rf $(OBJDIR) $(OUTDIR) *.o *.bin *.iso
	@echo "$(CGREEN)[✓] Cleaned all build artifacts$(CEND)"

re:		clean build
# ==============================
# Utility
# ==============================
$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/utils
	mkdir -p $(OBJDIR)/ascii
	@echo "$(CGREEN)[✓] $(OBJDIR) directory created$(CEND)"

.PHONY: all build run clean
