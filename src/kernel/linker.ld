ENTRY(_start)
OUTPUT_FORMAT("binary")
SECTIONS
{
    . = 0x7E00;
    .text        : {
        *(.text.boot)
        *(.text)
    }
    .data        : { *(.data) }
    .rodata      : { *(.rodata) }
    .bss         : { *(.bss) }
}