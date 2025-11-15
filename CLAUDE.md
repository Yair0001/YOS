# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

YOS is a custom x86 operating system written from scratch. It uses a 2-stage boot process and is compiled with a cross-compiler toolchain (i686-elf-gcc). The OS boots in real mode, transitions to protected mode, and runs the kernel at 0x7E00.

## Build System

### Required Tools
- `nasm` - Assembler for x86 assembly files
- `i686-elf-gcc` - Cross-compiler for 32-bit x86 targets
- `i686-elf-ld` - Linker for 32-bit x86 targets
- `qemu-system-i386` - Emulator for testing

### Common Commands

**Build the OS:**
```bash
make
```

**Clean build artifacts:**
```bash
make clean
```

**Run in QEMU:**
```bash
make run
```

**Debug mode (with interrupt logging and no reboot):**
```bash
make debug
```

**Verify OS image structure:**
```bash
make verify
```

### Build Output

- `bin/os.bin` - Final bootable OS image (stage1 + kernel concatenated)
- `bin/stage1.bin` - First stage bootloader (512 bytes, MBR)
- `bin/kernel.bin` - Kernel binary (loaded at 0x7E00)
- `build/` - Intermediate object files and build artifacts

## Architecture

### Boot Process

The OS uses a 2-stage boot architecture:

1. **Stage 1 (src/boot/stage1.asm)**: MBR bootloader (512 bytes)
   - Loaded by BIOS at 0x7C00
   - Reads kernel from disk using CHS addressing (BIOS interrupt 0x13)
   - Sector count is dynamically calculated by Makefile based on kernel size
   - Uses `KERNEL_SECTORS` define passed from Makefile during assembly
   - Jumps to kernel at 0x7E00
   - Disk layout: Sector 0 = stage1, Sector 1+ = kernel

2. **Kernel (src/kernel/)**: Main OS kernel
   - Entry point: `_start()` in kernel.asm
   - Loaded at 0x7E00 by stage1
   - Transitions to 32-bit protected mode
   - Sets up GDT (Global Descriptor Table)
   - Enables A20 line for accessing memory above 1MB
   - Calls `kern_main()` in main.c
   - Currently prints welcome message and halts

### Memory Layout

- **0x7C00**: Stage1 bootloader loaded here by BIOS
- **0x7E00**: Kernel loaded here by stage1
- **0x9C00**: Stack pointer for protected mode
- **0xB8000**: VGA text mode buffer (80x25 characters)

### Kernel Components

**Assembly (src/kernel/kernel.asm):**
- `_start()` - Entry point
- Protected mode setup (GDT, A20 line)
- Jumps to C code at `kern_main()`

**C Code (src/kernel/main.c):**
- `kern_main()` - Main kernel function
- Currently displays welcome message

### Common Utilities (src/common/)

Shared code used by the kernel:

- **printk**: VGA text mode output system
  - Direct VGA memory writes to 0xB8000
  - Printf-style formatting support
  - Manages screen offset and scrolling
  - Color support via VGA_COLOR enum
  - Supports: %s (string), %c (char), %d (signed int), %u (unsigned int), %x (hex), %p (pointer)

- **symbol.c**: Symbol table for formatted output parsing
- **intconv.c**: Integer to string conversions (itoa, utoa, xtoa)

## Compiler Flags

- `-ffreestanding`: No standard library
- `-nostdlib -nostartfiles -nodefaultlibs`: No default libraries or startup code
- `-g`: Include debug symbols
- `-O0`: No optimization (for easier debugging)
- `-Wall`: All warnings enabled
- `-I./src/common`: Common headers accessible to all components

## Linker Script

- **src/kernel/linker.ld**: Places kernel at 0x7E00, outputs raw binary format

## Known Constraints and Gotchas

1. **CHS addressing**: Using BIOS interrupt 0x13 for disk reads in stage1. Currently loads up to 64 sectors at once.

2. **Binary format**: Both bootloader and kernel output raw binary (no ELF headers) via linker script `OUTPUT_FORMAT(binary)`.

3. **Calling conventions**: Use `__attribute__((cdecl))` for C functions called from assembly.

4. **Entry point**: The kernel's `_start()` label in kernel.asm must be at the beginning of the binary.

## Makefile Structure

The build system uses a hierarchical Makefile structure with dynamic sector calculation:

- **Root Makefile**: Coordinates the build, assembles final OS image
- **src/boot/Makefile**: Builds stage1.bin with dynamically calculated KERNEL_SECTORS
- **src/common/Makefile**: Compiles common utilities (printk, symbol, intconv)
- **src/kernel/Makefile**: Builds kernel (kernel.asm + main.c + common objects)

Build order:
1. Common utilities
2. Kernel (depends on common)
3. Calculate kernel size in sectors → `build/kernel_sectors.txt`
4. Stage1 (reads kernel_sectors.txt and passes `-DKERNEL_SECTORS=N` to nasm)
5. Concatenate stage1 + kernel into os.bin

**Dynamic Sector Calculation:**
- The root Makefile calculates kernel size: `(size + 511) / 512`
- Stores sector count in `build/kernel_sectors.txt`
- boot/Makefile reads this file and passes it to nasm as a define
- stage1.asm uses `%ifdef KERNEL_SECTORS` to use the calculated value
- Falls back to 64 sectors if not defined (for standalone builds)

## Future Plans

- Switch to UEFI (noted in README.md as future work)
- Currently using legacy BIOS boot

## Testing

Run `make run` to test in QEMU. The kernel should print:
```
Welcome to YOS!
Kernel loaded at 0x7E00
System ready.
```
