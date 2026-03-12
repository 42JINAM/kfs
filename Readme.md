# How to run
### 1. Install **i686-elf**

Linux
```
sh ./install_compiler.sh
```
Mac
```
brew install i686-elf-gcc
```

### 2. Build iso image
```
make
or
make build
```
### 3. Run iso image in QEMU
```
make run
```

# How does it work?
## Process overview
```
src/*.c, src/*.s
        │
        ▼
   Compile → objs/*.o
        │
        ▼
   Link (linker.ld) → kernel.bin
        │
        ▼
   Create ISO (grub.cfg + kernel.bin) → kfs-1.iso
        │
        ▼
   Boot with GRUB → CPU executes kernel_main
```

## 1. Compile
Files involved: `src/*.c`, `src/boot.s` -> `objs/*.o`

1. Use a cross-compiler `i686-elf-gcc` to create object files (*.o)

### Cross-compiler ?
A cross-compiler is a compiler that runs on one platform (e.g., your PC) but generates machine code for a different target platform (e.g., the 32-bit x86 architecture).

### What does `boot.s` do?
- Declare constants for the multiboot header
- Define the multiboot header
- Allocate stack memory for the kernel
- Call the C kernel entry point

Learn more about [Bootstrap Assembly](https://wiki.osdev.org/Bare_Bones_with_NASM)

## 2. Link
Files involved: `linker.ld`, `objs/*.o` -> `kernel.bin`

1. All object files are linked together into a single executable kernel binary (`kernel.bin`).

2. During compilation, the compiler uses the linker script (linker.ld) to prepare **memory addresses** for each section (code, data, stack).

### Why is custom linker needed?

The kernel runs **without an operating system**, so the CPU needs exact memory addresses for code and data. 

And `linker.ld` specifies this memory layout.

Learn more about [linker script](https://wiki.osdev.org/Linker_Scripts)


## 3. Create ISO
Files involved: `grub.cfg`, `kernel.bin` -> `kfs-1.iso`

1. Copy the kernel binary and GRUB configuration (`grub.cfg`) into an ISO file system structure.

2. Use `xorriso` to generate a bootable ISO (`kfs-1.iso`).
  - GRUB can find and load the kernel from the ISO.

### ISO file system structure
GRUB requires specific structure to create iso file.
```
iso/
 └── boot/
      ├── kernel.bin
      └── grub/
           └── grub.cfg
```

## 4. Boot with [GRUB](https://wiki.osdev.org/GRUB#Using_GRUB_to_boot_your_OS)
Files involved: `grub.cfg`, `kfs-1.iso`

1. Boot the ISO using QEMU or real hardware.

2. GRUB starts and reads `grub.cfg`.

  - It finds the kernel path and name inside the ISO.

3. GRUB loads the kernel into memory.

4. The CPU jumps to the kernel entry point (kernel_main).

5. The kernel takes control, initializes the terminal, VGA, and other basic systems.

## Useful link
[I/O handling](https://wiki.osdev.org/Inline_Assembly/Examples)

### keyboard input
[Receiving Bytes From Device/s](https://wiki.osdev.org/index.php?title=I8042_PS/2_Controller)

[Keyboard](https://osdev.jsren.co.uk/input-output/keyboard)
