extern unsigned long _sbss;
extern unsigned long _ebss;

extern int user_main(void);


void GCC_Reset_Handler(void)
{
	unsigned long  *pulDest;

    // Zero fill the bss segment.
    //
    for(pulDest = &_sbss; pulDest < &_ebss; )
    {
        *(pulDest++) = 0;
    }
			
    //
    // Call the application's entry point.
    //
    user_main();
}
