# ECU can system

System for controlilng auto(scooter, bycycle) electronic blocks by CAN bus.

## General deacription

MCU pins:
PORT     - CAN_H
PORT     - CAN_L
PORT     - dipped lights
PORT     - headlights 
PORT     - parking lights
PORT     - current measurment
PORT     - voltage measurment
PORT     - I2C_DATA
PORT     - I2C_CLK

### Block_1: Headlight ECU
CAN ID:
Function:
- Dipped beam headlights
- Headlights of distant light
- Parking lights
- Current and Voltage measure for dignostic

CAN command:
- Light_on_fast
- Light_off_fast
- Light_on_slow
- Light_off_slow
- Light_set_brightness
- Light_all_get_voltage_and_current
- Light_all_get_state


 
 
 