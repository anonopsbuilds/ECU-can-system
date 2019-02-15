# ECU can system

System for controlilng auto(scooter, bycycle) electronic blocks by CAN bus.

## General deacription

MCU pins:   
* PA12 - CAN_TX   
* PA11 - CAN_RX   
* PB0 - dipped lights    
* PA6 - headlights   
* PA7 - parking lights   
* PA1 - current measurment   
* PA0 - voltage measurment   
* PB7- I2C_DATA     
* PB6- I2C_CLK  

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


 
 
 