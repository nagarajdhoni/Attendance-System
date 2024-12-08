#include "header.h"

extern u8 flag;           // Flag to indicate data received status
char rfid[13];            // Buffer to store RFID data
char timing[40];          // Buffer to store formatted time
char str[55];             // Buffer for concatenated RFID and time data

// Initialize system peripherals: I2C, LCD, UART, and interrupts
void SystemInitialization(void) {
    i2c_init();                    
    lcd_init();                    
    uart0_init(9600);              
    config_vic_for_uart0();        
    config_uart0_interrupt();      
}

int main() {
    time t;                        
    SystemInitialization();        
    
    uart0_string_tx("DS1307 RTC\r\n"); 

    // Set initial time on RTC (HH:MM:SS, Day, Date, Month, Year)
    set_time(0x00, 0x40, 0x52, 0x01, 0x12, 0x05, 0x11);

    while (1) {
        if (flag == 1) {           
            flag = 0;              
            lcd_cmd(0x80);         
            t = read_time();       
            write_time(t);   
			      

            store_time(t, timing); 
            add_str(rfid, timing, str); 

            uart0_string_tx(str);  
        }
    }
}
