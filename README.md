# Mall Driveway Automation System

## Overview

This project is a mall driveway automation system built using an Arduino microcontroller. The system manages the entry and exit of vehicles in a parking lot, automatically controlling the gates and displaying the number of available parking slots. The project utilizes ultrasonic sensors to detect vehicle presence, servos to control gate movement, an LDR (Light Dependent Resistor) for ambient light detection, and an I2C LCD for displaying the status of the parking slots.

## Components

- **Arduino Uno**: The brain of the system that controls all the components.
- **Ultrasonic Sensor (HC-SR04)**: Measures the distance of vehicles to determine their presence at the entry and exit points.
- **Servos (2x)**: Used to control the gates (entry and exit).
- **LDR (Light Dependent Resistor)**: Detects the ambient light to control the LED.
- **LED**: Indicates when a vehicle is detected.
- **I2C LCD (16x2)**: Displays the number of available parking slots, vehicles entering, and vehicles exiting.
- **Wires and Resistors**: Connect various components to the Arduino.

## Circuit Connections

- **Ultrasonic Sensor**: 
  - `Trig` pin to Arduino pin 7
  - `Echo` pin to Arduino pin 6
- **Servos**: 
  - `Servo 1 (Entry Gate)` connected to Arduino pin 9
  - `Servo 2 (Exit Gate)` connected to Arduino pin 10
- **LDR**: Connected to Arduino pin 8
- **LED**: Connected to Arduino pin 13
- **I2C LCD**: Connected via the I2C bus (SDA and SCL pins)

## How It Works

1. **Detection**: The ultrasonic sensor at the entry gate detects if a vehicle is within range (less than 10 cm). The sensor at the exit gate detects vehicles within a range of 10 to 20 cm.
  
2. **Gate Control**: 
   - If a vehicle is detected at the entry gate and there are available slots, the entry gate opens, allowing the vehicle to enter, and the count of vehicles inside the parking lot is incremented.
   - If the parking lot is full, a message "PARKING FULL!! GO ELSEWHERE" is displayed on the LCD.
   - When a vehicle is detected at the exit gate, the exit gate opens, and the count of vehicles inside the parking lot is decremented.

3. **Display**: The LCD displays the number of available slots, vehicles inside, and vehicles that have exited.

4. **Light Indicator**: The LED lights up when a vehicle is detected, providing a visual cue.

## Code Explanation

- **setup()**: Initializes the serial communication, sets up pin modes, attaches the servos, and initializes the LCD.
- **loop()**: Continuously checks for the presence of vehicles using the ultrasonic sensor and controls the gates based on the parking availability. The status of the parking lot is updated on the LCD.

## Usage

1. **Power Up**: Connect the Arduino to a power source or computer.
2. **Observe the LCD**: The display will show the current status of the parking slots.
3. **Vehicle Detection**: The system will automatically detect vehicles and control the gates accordingly.

## Future Enhancements

- Integrating a system to count available parking slots based on real-time data.
- Implementing a mobile app to display parking availability remotely.
- Adding RFID or camera-based vehicle recognition for enhanced security.

## Troubleshooting

- **LCD Not Displaying**: Check the I2C connections and the address set in the code.
- **Servos Not Moving**: Ensure proper power supply and that the servos are attached correctly in the code.
- **No Distance Measurement**: Verify the connections of the ultrasonic sensor and ensure it's facing the correct direction.

This project automates the vehicle entry and exit process in a mall parking lot, providing convenience and efficiency for users.
