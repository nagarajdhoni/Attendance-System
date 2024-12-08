#include <lpc21xx.h>

typedef unsigned int u32;
typedef unsigned char u8;

// Time structure for RTC operations
typedef struct timer {
    u8 sec, min, hour, day, date, mon, year;
    char AP[3];  // AM/PM indicator
} time;

// DELAY FUNCTION
extern void delay_ms(u32);

// LCD FUNCTIONS
extern void lcd_init(void);
extern void lcd_cmd(u8);
extern void lcd_data(u8);
extern void lcd_string(char *);
extern void lcd_hex(u8);

// UART0 FUNCTIONS
extern void uart0_init(u32);
extern void uart0_tx(u8);
extern u8 uart0_rx(void);
extern void uart0_string_tx(char *);
extern void uart0_string_rx(char *,int);

// UART0 INTERRUPT FUNCTIONS
extern void config_vic_for_uart0(void);
extern void config_uart0_interrupt(void);

// I2C FUNCTIONS
extern void i2c_init(void);
extern void i2c_byte_write_frame(u8,u8,u8);
extern u8 i2c_byte_read_frame(u8,u8);

// TIME FUNCTIONS
extern void set_time(u8,u8,u8,u8,u8,u8,u8);
extern time read_time(void);
extern void write_time(time);
extern int mystrcmp(const char *, const char *);