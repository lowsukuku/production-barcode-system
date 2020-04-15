/* Memory Spaces Definitions */
MEMORY
{
/* change SDRAM ORIGIN also change the the application's entry point address */
/* change SDRAM ORIGIN  */
	SDRAM (xrw) : ORIGIN = 0x83f80000, LENGTH = 512K
/* change SDRAM ORIGIN  */
	NORFLASH (rx) : ORIGIN = 0x00620000, LENGTH = 1M
}


SECTIONS
{	
    PROVIDE(SysCallLib = 0x80000634);
	/*PROVIDE(SysCallLib = 0x800008d0);*/

	
	.text 0x83f80000 :  
    {
	    . = ALIGN(4);
	    
        lib\src\ms3590_vector.o(.text)                   /* remaining code */
	    lib\src\ms3590_vector.o(.text.*)                    /* remaining code */
        lib\src\ms3590_vector.o(.rodata)                 /* read-only data (constants) */
		lib\src\ms3590_vector.o(.rodata*)
		
	    . = ALIGN(4);
    } >SDRAM AT>NORFLASH
        
    /* the program code is stored in the .text section, which goes to Flash */
    .text :  
    {
	    . = ALIGN(4);
	    
        *(.text)                  /* remaining code */
        *(.text.*)                  /* remaining code */
        *(.rodata)                 /* read-only data (constants) */
        *(.rodata*) 

	    . = ALIGN(4);
   	 _etext = .;
	    /* This is used by the startup in order to initialize the .data secion */
   	 _sidata = _etext;
    } >SDRAM AT>NORFLASH
    
 
    /* This is the initialized data section
    The program executes knowing that the data is in the RAM
    but the loader puts the initial values in the FLASH (inidata).
    It is one task of the startup to copy the initial values from FLASH to RAM. */
    .data  :
    {
	    . = ALIGN(4);
        /* This is used by the startup in order to initialize the .data secion */
        _sdata = . ;
        
        *(.data)
        *(.data.*)

	    . = ALIGN(4);
	    /* This is used by the startup in order to initialize the .data secion */
   	 _edata = . ;
    } >SDRAM AT>NORFLASH
    
    

    /* This is the uninitialized data section */
    .bss : 
    {
	    . = ALIGN(4);
        /* This is used by the startup in order to initialize the .bss secion */
        _sbss = .;
        
        *(.bss)
        *(COMMON)
            . = ALIGN(4);
	    /* This is used by the startup in order to initialize the .bss secion */
   	 _ebss = . ;
    } >SDRAM AT>NORFLASH
    
    PROVIDE ( _end = _ebss );
}