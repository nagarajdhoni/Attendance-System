#include "header.h"

#define UART0 (1<<6) // Enable UART0 interrupt
#define START (1<<5) // Slot0 EN Bit


extern char rfid[13]; 
u8 flag = 0;           

// UART0 interrupt handler to read RFID data
void uart0_handler(void) __irq {
    static int index = 0;            
    u8 interrupt_id = U0IIR & 0xE;   

    if (interrupt_id == 4) {         // Check if it's a received data interrupt
        rfid[index] = U0RBR;         
        U0THR = rfid[index];         

        if (rfid[index++] == '\r' || index == 13) { 
            rfid[index - 1] = '\0';  
            index = 0;               
            flag = 1;                
        }
    }
    VICVectAddr = 0;                 
}

// Enable interrupt in VIC and link to UART0 handler
void config_vic_for_uart0(void) {
    VICIntEnable = UART0;           
    VICVectCntl0 = 6 | START;     
    VICVectAddr0 = (u32)uart0_handler; 
}

// Enable receive interrupt for UART0
void config_uart0_interrupt(void) {
    U0IER = 1;                       
}
