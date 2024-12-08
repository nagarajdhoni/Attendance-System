#include "header.h"

#define I2EN        (1 << 6)       // I2C enable
#define STA         (1 << 5)       // Start condition
#define STO         (1 << 4)       // Stop condition
#define SI          (1 << 3)       // Interrupt flag
#define SI_FLAG     ((I2CONSET >> 3) & 1)  // I2C interrupt flag status

#define SET_START   I2CONSET = STA         // Set start condition
#define SET_STOP    I2CONSET = STO         // Set stop condition
#define CLEAR_SI    I2CONCLR = SI          // Clear SI flag

// Initialize I2C interface 
void i2c_init(void) {
    PINSEL0 |= 0x50;            
    I2SCLH = I2SCLL = 75;       // Set clock speed 
    I2CONSET = I2EN;            
}

// Send a single byte over I2C to a specific register address
void i2c_byte_write_frame(u8 slave_addr, u8 reg_addr, u8 data) {
    SET_START;                  
    CLEAR_SI;                   
    while (!SI_FLAG);           

    I2DAT = slave_addr;         
    CLEAR_SI;                   
    while (!SI_FLAG);           

    I2DAT = reg_addr;           
    CLEAR_SI;                   
    while (!SI_FLAG);           

    I2DAT = data;               
    CLEAR_SI;                   
    while (!SI_FLAG);           

    SET_STOP;                   
}

// Read a single byte from a specified I2C register address
u8 i2c_byte_read_frame(u8 slave_addr, u8 reg_addr) {
    u8 data;

    SET_START;                  
    CLEAR_SI;                   
    while (!SI_FLAG);           

    I2DAT = slave_addr;         
    CLEAR_SI;                   
    while (!SI_FLAG);           

    I2DAT = reg_addr;           
    CLEAR_SI;                   
    while (!SI_FLAG);           

    data = I2DAT;               
    SET_STOP;                   
    return data;                
}
