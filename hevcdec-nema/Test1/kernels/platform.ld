OUTPUT_FORMAT("elf32-nemaweaver-little", "elf32-nemaweaver-little", "elf32-nemaweaver-little")
 SECTIONS
 {
 .text :
 {
 *(.text*)
 }
 
 . = ALIGN(16);
 .rodata : { *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*))) }
 
 . = ALIGN(16);
 .data : { *(.data*) }
 
 . = .;
 _gp = ALIGN(16) + 0x7ff0;
 
 .got : {
 __got_start = .;
 *(.got)
 __got_end = .;
 }
 
 .sdata : { *(.sdata*) }
 
 . = ALIGN(16);
 __bss_start = .;
 .sbss (NOLOAD) : { *(.sbss*) }
 .bss (NOLOAD) : { *(.bss*) . = ALIGN(4); }
 
 _end = .;
 }
