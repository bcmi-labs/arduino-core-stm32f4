/*
 * aeroquad32 (STM32F469BIT6) linker script for
 * JTAG (bare metal, no bootloader) builds.
 */

MEMORY
{
  /* As per Keil linker script we have 320kB RAM.
   * Leave last 4kB free for housekeeping variables, e.g.: DFU */
  ram (rwx) : ORIGIN = 0x20000000, LENGTH = 316K
  rom (rx)  : ORIGIN = 0x08000000, LENGTH = 2048K
}

/* GROUP(libcs3_stm32_high_density.a) */

REGION_ALIAS("REGION_TEXT", rom);
REGION_ALIAS("REGION_DATA", ram);
REGION_ALIAS("REGION_BSS", ram);
REGION_ALIAS("REGION_RODATA", rom);

_FLASH_BUILD = 1;
INCLUDE common.inc
