# RFID Time Attendance System

## Overview
This project implements a Real-Time Clock (RTC) based RFID attendance system using an LPC2148 microcontroller. The system captures RFID card data and timestamps each entry/exit, providing a reliable solution for attendance tracking in organizations.

## Features
- **Real-time clock integration** using DS1307 RTC module
- **16x2 LCD display** for showing current time and status
- **RFID card reading capability**
- **Serial communication** for data logging
- **AM/PM time format** support
- **Date and day of the week** display
- **Attendance logging** with entry/exit tracking
- **Data persistence** through file storage

## Hardware Components
- **LPC2148 Microcontroller**
- **DS1307 RTC Module**
- **16x2 LCD Display**
- **RFID Reader Module**
- **FTDI USB-UART Cable**
- **Supporting passive components**

## Software Architecture

### Core Modules
- **RTC Interface (Read_Timer.c)**: 
  - Time reading and setting functions
  - Date and time formatting
  - AM/PM conversion
- **I2C Communication (I2C_Driver.c)**: 
  - I2C protocol implementation
  - RTC communication handling
  - Register read/write operations
- **LCD Control (LCD_Driver.c)**: 
  - 4-bit mode LCD interface
  - Display formatting and control
  - Custom character support
- **UART Communication (UART0_Driver.c, UART0_Interrupt.c)**: 
  - Serial communication setup
  - Interrupt-driven RFID data reception
  - Data transmission protocols
- **Linux Interface (linux2.c)**: 
  - Serial port configuration
  - Data logging and file operations
  - RFID validation and record keeping

## Key Features Implementation
- **Time Management**: Using the DS1307 RTC, the system tracks and displays the current time, date, and day of the week.
- **Attendance Logging**: RFID cards are scanned to record entry/exit times. Data is logged to a file with timestamps.

## Setup and Configuration

### Hardware Setup
1. Connect the DS1307 RTC module to the I2C pins (SCL, SDA).
2. Wire the LCD display to the designated GPIO pins.
3. Connect the RFID reader to the UART0 pins.
4. Ensure proper power supply connections.

### Software Configuration
1. Set the initial RTC time using the `set_time()` function.
2. Configure UART baud rate (default: 9600).
3. Set up data storage files (`data` and `record`).
4. Adjust timing parameters if needed.

## Usage
1. Power up the system.
2. The system initializes and displays the current time.
3. Scan an RFID card:
   - The system will validate the card against the database.
   - It will record the entry/exit with a timestamp.
   - The status will be displayed on the LCD.
   - Data will be logged to the storage file.


