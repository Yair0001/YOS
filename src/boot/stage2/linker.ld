ENTRY(_start)
OUTPUT_FORMAT("binary")
SECTIONS {
    . = 0x7e00;
    .text        : { *(.text) }
    .data        : { *(.data) }
    .rodata      : { *(.rodata) }
    .bss         : { *(.bss) }
}