#include "header.h"

// Compare two strings
int mystrcmp(const char *str1, const char *str2) {
    while (*str1 == *str2) {
        if (*str1 == '\0') return 0;  
        str1++;
        str2++;
    }
    return *str1 - *str2;             
}

// Concatenate two strings into a third
void add_str(char *a, char *b, char *c) {
    int i = 0, j = 0, k = 0;

    while (a[i]) c[k++] = a[i++];    
    while (b[j]) c[k++] = b[j++];    
    c[k] = '\0';                     
}

// Format and store time in string
void store_time(time t, char *timing) {
    int i = 0;

    timing[i++] = (t.hour / 16) + '0';   // Format hours
    timing[i++] = (t.hour % 16) + '0';
    timing[i++] = ':';
    timing[i++] = (t.min / 16) + '0';    // Format minutes
    timing[i++] = (t.min % 16) + '0';
    timing[i++] = ':';
    timing[i++] = (t.sec / 16) + '0';    // Format seconds
    timing[i++] = (t.sec % 16) + '0';
    timing[i++] = ' ';
    timing[i++] = (t.date / 16) + '0';   // Format date
    timing[i++] = (t.date % 16) + '0';
    timing[i++] = '/';
    timing[i++] = (t.mon / 16) + '0';    // Format month
    timing[i++] = (t.mon % 16) + '0';
    timing[i++] = '/';
    timing[i++] = (t.year / 16) + '0';   // Format year
    timing[i++] = (t.year % 16) + '0';
    timing[i] = '\0';                    
}

// Write specified time to RTC over I2C
void set_time(u8 sec, u8 min, u8 hour, u8 day, u8 date, u8 mon, u8 year) {
    i2c_byte_write_frame(0xD0, 0x0, sec);   // Set seconds
    i2c_byte_write_frame(0xD0, 0x1, min);   // Set minutes
    i2c_byte_write_frame(0xD0, 0x2, hour);  // Set hours
    i2c_byte_write_frame(0xD0, 0x3, day);   // Set day of week
    i2c_byte_write_frame(0xD0, 0x4, date);  // Set date
    i2c_byte_write_frame(0xD0, 0x5, mon);   // Set month
    i2c_byte_write_frame(0xD0, 0x6, year);  // Set year
    lcd_string("Time updated");             // Display update message
    delay_ms(1000);
    lcd_cmd(0x01);                          
}

// Read current time from RTC
time read_time(void) {
    time t;

    t.sec = i2c_byte_read_frame(0xD0, 0x0);   // Read seconds
    t.min = i2c_byte_read_frame(0xD0, 0x1);   // Read minutes
    t.hour = i2c_byte_read_frame(0xD0, 0x2);  // Read hours
    t.day = i2c_byte_read_frame(0xD0, 0x3);   // Read day
    t.date = i2c_byte_read_frame(0xD0, 0x4);  // Read date
    t.mon = i2c_byte_read_frame(0xD0, 0x5);   // Read month
    t.year = i2c_byte_read_frame(0xD0, 0x6);  // Read year

    // Determine AM/PM for 12-hour format
    if ((t.hour >> 5) & 1) {
        t.AP[0] = 'P'; t.AP[1] = 'M'; t.AP[2] = '\0';
    } else {
        t.AP[0] = 'A'; t.AP[1] = 'M'; t.AP[2] = '\0';
    }
    return t;
}

void write_time(time t) {
    
    char *days[8] = {" ", "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    
    lcd_cmd(0x01); 
	
	lcd_cmd(0x89);          
		
    if ((t.hour >> 5) & 1) {
        lcd_string("PM");
    } else {
        lcd_string("AM");
    }
	         
    lcd_cmd(0x80);          

    t.hour = t.hour & 0x1F; 

    lcd_hex(t.hour);        // hours
    lcd_data(':');          
    lcd_hex(t.min);         // minutes
    lcd_data(':');          
    lcd_hex(t.sec);         // seconds
    

    lcd_cmd(0xC0);          // Next Line
		
         

    // Display date in DD/MM/YY format
    lcd_hex(t.date);        
    lcd_data('/');          
    lcd_hex(t.mon);         
    lcd_data('/');          
    lcd_string("20");       
    lcd_hex(t.year); 
	lcd_data(' ');   
	
	lcd_string(days[t.day]); // day name
    
}
