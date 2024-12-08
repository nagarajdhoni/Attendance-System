#include "header.h"

#define THRE ((U0LSR >> 5) & 1) // Transmitter Holding Register Empty flag
#define RDR  (U0LSR & 1)        // Receiver Data Ready flag

// Initialize UART0 
void uart0_init(u32 baud) {
    int pclk_div[] = {15, 60, 30, 15, 15};    
    u32 pclk = pclk_div[VPBDIV] * 1000000; 
    u32 divisor = pclk / (16 * baud);      

    PINSEL0 |= 5;          // Set UART0 pins for Rx & Tx
    U0LCR = 0x83;          // Enable DLAB to set baud rate
    U0DLL = divisor & 0xFF;
    U0DLM = (divisor >> 8) & 0xFF;
    U0LCR = 0x03;          // 8-bit character length, DLAB disable
}

// Transmit char
void uart0_tx(u8 data) {
    U0THR = data;          
    while (THRE == 0);     
}

// Receive char
u8 uart0_rx(void) {
    while (RDR == 0);      
    return U0RBR;          
}

// Transmit string 
void uart0_string_tx(char *str) {
    while (*str) {
        uart0_tx(*str++);  
    }
}

// Receive string 
void uart0_string_rx(char *ptr, int len) {
    int i;
    
    for (i = 0; i < len - 1; i++) {       
        ptr[i] = uart0_rx();              
        
        if (ptr[i] == '\r') {             
            break;                        
        }
    }
    
    ptr[i] = '\0';                        
}

