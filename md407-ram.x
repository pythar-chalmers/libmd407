/*
	Default linker script for MD407 (STM32F407)
	All code and data goes to RAM.
*/

MEMORY
{
	RAM (xrw) : ORIGIN = 0x20000000, LENGTH = 108K
}

SECTIONS
{
	.text :
	{
		. = ALIGN(4);
		*(.start_section) /* startup code */
		*(.text)          /* remaining code */
		*(.text.*)
		*(.bss)           /* unintialised data */
		*(COMMON)
		*(.data)          /* initialised data */
		*(.data.*)
		*(.rodata)        /* read-only data (constants) */
		*(.rodata.*)
		. = ALIGN(4);
	} >RAM
}
