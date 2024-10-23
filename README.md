# M5Tough Painting App

## Overview
This project utilizes the M5Tough library to create a simple interactive painting application for the M5Tough device. 
Users can select between two colors (RED or BLUE) and reset the device using three on-screen buttons. 
The app draws circles in the selected color at the user's touch position.

## Features
- **Color Selection**: Users can choose between RED and BLUE colors.
- **Reset Functionality**: The device can be restarted using the reset button.
- **Interactive Drawing**: Draws circles at the touch position with the selected color.

## Requirements
- **Hardware**: M5Tough device
- **Software**: Arduino IDE with M5Tough library installed

## Installation
1. **Setup the Arduino IDE**: Make sure you have the Arduino IDE installed on your computer.
2. **Install M5Tough Library**: In the Arduino IDE, go to `Sketch` -> `Include Library` -> `Manage Libraries...`, search for "M5Tough", and install it.
3. **Upload the Code**: Copy the provided code into a new Arduino sketch. Connect your M5Tough device to your computer and upload the sketch.

## Code Explanation

### Button Definitions
- **Button 1 ("RED")**: Sets the current color to RED when tapped.
- **Button 2 ("BLUE")**: Sets the current color to BLUE when tapped.
- **Button 3 ("RESET")**: Restarts the ESP32 device when tapped.

### Main Loop
The main loop continuously checks for touch events and draws a circle at the current touch position using the selected color.

### Event Handlers
- `eventDisplayBUTTON1`: Changes the color to RED.
- `eventDisplayBUTTON2`: Changes the color to BLUE.
- `eventDisplayBUTTON3`: Restarts the device.

### Drawing Function
- `circle(Point p, uint16_t c)`: Draws a filled circle at the specified point with the specified color.

## Usage
1. Tap the "RED" button to select the red color.
2. Tap the "BLUE" button to select the blue color.
3. Touch anywhere on the screen to draw a circle in the selected color.
4. Tap the "RESET" button to restart the device.

## Troubleshooting
- If the device does not respond, check the connections and ensure the M5Tough library is correctly installed.
- If the screen does not display correctly, try resetting the device.

## License
This project is open-source. Feel free to modify and distribute the code under the terms of the MIT License.

## Acknowledgments
- Thanks to the M5Stack community for their support and resources.