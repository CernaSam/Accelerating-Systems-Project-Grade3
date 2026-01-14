/* Simple UART Test - Replace main.c temporarily with this */
#include "platform.h"
#include "xil_printf.h"

int main(void)
{
    init_platform();
    
    // Use xil_printf which goes directly to UART
    xil_printf("\n\n\r");
    xil_printf("========================================\n\r");
    xil_printf("UART TEST - If you see this, UART works!\n\r");
    xil_printf("========================================\n\r");
    xil_printf("Test message 1\n\r");
    xil_printf("Test message 2\n\r");
    xil_printf("Test message 3\n\r");
    
    // Infinite loop so program doesn't exit
    while(1) {
        // Blink test
        for(volatile int i = 0; i < 10000000; i++);
        xil_printf("Still running...\n\r");
    }
    
    cleanup_platform();
    return 0;
}
