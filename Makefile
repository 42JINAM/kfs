# AS     := i686-elf-as
AS     := nasm 
CC     := i686-elf-gcc
LD     := i686-elf-gcc

OBJDIR := objs
SRCDIR := src


CFILES = strlen \
				 kernel

SFILES = boot

C_OBJCS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(CFILES)))
S_OBJCS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SFILES)))
OBJS = $(C_OBJCS) $(S_OBJCS)

all: kfs-1.iso

kfs-1.bin: $(OBJS) linker.ld | $(OBJDIR)
	$(LD) -nostdlib -ffreestanding -O2 \
	      -T linker.ld -o $@ $(OBJS) -lgcc

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostdlib -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.s | $(OBJDIR)
	$(AS) -f elf $< -o $@

kfs-1.iso: kfs-1.bin grub.cfg
	rm -rf output
	mkdir output
	docker compose up --build
	cp output/kfs-1.iso .

run: kfs-1.iso
	qemu-system-i386 -cdrom kfs-1.iso 

clean:
	rm -rf $(OBJDIR) *.o kfs-1.bin *.iso output

$(OBJDIR):
	mkdir -p $(OBJDIR)

.PHONY: all run debug clean

