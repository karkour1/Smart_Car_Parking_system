# Smart Car Parking System

## Overview
The **Smart Car Parking System** automates parking management by detecting available slots and controlling entry/exit barriers. Vehicles are identified by unique IDs at entry and exit points, and real-time parking availability is displayed on LCD screens. This system is designed for efficient space management in modern parking lots.

## Features
- **ID-Based Vehicle Management**: Unique IDs for vehicle entry and exit via USART or keypad.
- **Real-Time Slot Monitoring**: LCD displays for available parking slots.
- **Servo-Controlled Barriers**: Automatically opens/closes based on ID verification.
- **Input/Output Sensors**: PIR sensors for vehicle detection at gates.

## Hardware Components
- **Microcontroller**: STM32F103C8T6 (Blue Pill)
- **LCD Displays**: Two 16x2 LCDs for slot updates
- **Servo Motors**: Two servos for entry/exit barriers
- **Keypad**: For inputting slot numbers and IDs
- **PIR Sensors**: Detect vehicles at entry/exit points
- **LEDs**: Green/Red LEDs for status indication

## Software Components
- **USART Communication**: Handles vehicle IDs
- **Servo Control**: Manages servo movement for barriers
- **LCD Interface**: Displays messages and available slots
- **PIR Integration**: Triggers barrier movement upon vehicle detection

## Code Structure
- **SCP_application.c**: Main logic for ID processing, servos, and LCD updates
- **SCP_application.h**: Function prototypes and global variables
- **Servo.h/Servo.c**: Servo motor control
- **LCD.h/LCD.c**: LCD display management
- **USART Drivers**: Handle UART communication for vehicle IDs

## Usage
### System Initialization:
- Power on the system and enter the total number of parking slots via the keypad.
- The LCD displays a welcome message and waits for input.

### Entry Process:
- Enter vehicle ID via USART. If valid and slots are available, the barrier opens, and the slot count updates.

### Exit Process:
- Verify vehicle ID at the exit via USART. If valid, the barrier opens and updates the slot count.

### Managing IDs
- Add or remove vehicle IDs using keypad commands for smooth entry/exit.

## Future Improvements
- **Web/Mobile App Interface**: Monitor parking status via a web or mobile application.
- **Enhanced Security**: Add cameras for vehicle tracking and improved security.

