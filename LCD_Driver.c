#include "header.h"

#define RS (1 << 17)  // Register Select (RS) pin for command/data control
#define RW (1 << 18)  // Read/Write (RW) pin (set low for write)
#define EN (1 << 19)  // Enable (EN) pin to latch data

// Send a command to the LCD
void lcd_cmd(u8 cmd) {
    u32 temp = (cmd & 0xF0) << 16;   
    IOCLR1 = 0xFE << 16;             
    IOSET1 = temp;                   
    IOCLR1 = RS;                     
    IOCLR1 = RW;                     
    IOSET1 = EN;                     
    delay_ms(2);
    IOCLR1 = EN;                     

    temp = (cmd & 0x0F) << 20;       
    IOCLR1 = 0xFE << 16;             
    IOSET1 = temp;                   
    IOCLR1 = RS;                     
    IOCLR1 = RW;                     
    IOSET1 = EN;                     
    delay_ms(2);
    IOCLR1 = EN;
}

// Send data (character) to the LCD
void lcd_data(u8 data) {
    u32 temp = (data & 0xF0) << 16;  
    IOCLR1 = 0xFE << 16;             
    IOSET1 = temp;                   
    IOSET1 = RS;                     
    IOCLR1 = RW;                     
    IOSET1 = EN;                     
    delay_ms(2);
    IOCLR1 = EN;

    temp = (data & 0x0F) << 20;      
    IOCLR1 = 0xFE << 16;             
    IOSET1 = temp;                   
    IOSET1 = RS;                     
    IOCLR1 = RW;                     
    IOSET1 = EN;                     
    delay_ms(2);
    IOCLR1 = EN;
}

// Initialize the LCD in 4-bit mode
void lcd_init(void) {
    IODIR1 |= 0xFE << 16;            
    PINSEL2 = 0;                     
    IOCLR1 = EN;                     

    lcd_cmd(0x02);                   // Initialize LCD in 4-bit mode
    lcd_cmd(0x28);                   // Set 2-line for 4-bit mode
    lcd_cmd(0x0C);                   // Display ON, cursor OFF
    lcd_cmd(0x01);                   // Clear display
}

// Display a string on the LCD
void lcd_string(char *p) {
    while (*p) {
        lcd_data(*p++);              
    }
}

// Display a hexadecimal number on the LCD
void lcd_hex(u8 num) {
//    char buffer[8];
//    int i = 0;
//
//    if (num == 0) {
//        lcd_data('0');
//        return;
//    }
//
//    // Convert number to hex digits
//    while (num) {
//        u8 digit = num & 0xF;
//        buffer[i++] = (digit < 10) ? digit + '0' : digit + 'A' - 10;
//        num >>= 4;
//    }
//
//    // Display hex number in correct order
//    while (i > 0) {
//        lcd_data(buffer[--i]);
//    }

	lcd_data((num/16)+48);
	lcd_data((num%16)+48);
}
