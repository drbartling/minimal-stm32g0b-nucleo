/* memory layout for an STM32F401RE */

MEMORY
{
	FLASH(rx) : ORIGIN = 0x08000000, LENGTH = 256K
	RAM(xrx)  : ORIGIN = 0x20000000, LENGTH = 144K
}

/* output sections */
SECTIONS
{
	/* Program code into FLASH */
	.text : ALIGN(4)
	{
		*(.isr_vector)
		*(.text)
		*(.text*)
		KEEP(*(.isr_vector))
	} >FLASH


	.data : ALIGN(4)
	{
		. = ALIGN(4);
		LINKER_start_data = .; /* Start of data memory in RAM*/

		*(.data)
		*(.data*)

		. = ALIGN(4);
		LINKER_end_data = .; /* End of data memory in RAM*/
	} >RAM AT>FLASH
	/* .data for ram and copy of initialized data AT (in) FLASH */

	/* Load address of initial global variable values */
	LINKER_load_data = LOADADDR(.data);
}
