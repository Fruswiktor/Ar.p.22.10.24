/*
 * M5Tough Color Picker Example
 *
 * This program utilizes the M5Tough library to create a simple interface
 * with three buttons on an M5Tough device. The buttons allow the user to 
 * select a color (RED or BLUE) and to reset the device.
 *
 * Button functionalities:
 * - Button 1 ("RED"): Sets the current color to RED when tapped.
 * - Button 2 ("BLUE"): Sets the current color to BLUE when tapped.
 * - Button 3 ("RESET"): Restarts the ESP32 device when tapped.
 *
 * The main loop continuously checks for button events and draws a circle
 * at the current touch position with the selected color.
 *
 * The screen is initialized in BLACK, and the buttons are displayed with
 * specified colors for their on/off states.
 *
 * Note: Ensure that the M5Tough library is included and configured correctly.
 */



#include <M5Tough.h>
#include <Arduino.h>

// Define button colors for on and off states
ButtonColors on_clrs = {GREEN, WHITE, WHITE};
ButtonColors off_clrs = {BLACK, WHITE, WHITE};

// Create buttons with specified positions, sizes, and labels
Button bl(20, 200, 80, 40, false, "RED", off_clrs, on_clrs, MC_DATUM);
Button b2(120, 200, 80, 40, false, "BLUE", off_clrs, on_clrs, MC_DATUM);
Button b3(220, 200, 80, 40, false, "RESET", off_clrs, on_clrs, MC_DATUM);

// Variable to store the currently selected color
uint16_t currentColor = RED;  

void setup() {
  // Initialize the M5Tough device
  M5.begin();
  // Fill the screen with black color
  M5.Lcd.fillScreen(BLACK);
  // Set text size for display
  M5.Lcd.setTextSize(2);
  // Set text datum to center the text
  M5.Lcd.setTextDatum(MC_DATUM);
  // Draw the buttons on the screen
  M5.Buttons.draw();
  // Add event handlers for button taps
  bl.addHandler(eventDisplayBUTTON1, E_TAP);
  b2.addHandler(eventDisplayBUTTON2, E_TAP);
  b3.addHandler(eventDisplayBUTTON3, E_TAP);
}

// Event handler for the RED button
void eventDisplayBUTTON1(Event& e) {
  // Check if the event is a tap
  if (e.type == E_TAP) {
    // Set the current color to RED
    currentColor = RED;  
  }
}

// Event handler for the BLUE button
void eventDisplayBUTTON2(Event& e) {
  // Check if the event is a tap
  if (e.type == E_TAP) {
    // Set the current color to BLUE
    currentColor = BLUE; 
  }
}

// Event handler for the RESET button
void eventDisplayBUTTON3(Event& e) {
  // Restart the ESP32 device
  ESP.restart();
}

void loop() {
  // Update the M5Tough state
  M5.update();

  // Reference to the button event
  Event& e = M5.Buttons.event;

  // Check if the event is a movement or gesture
  if (e & (E_MOVE | E_GESTURE)) {
    // Draw a circle at the touch position with the current color
    circle(e.to, currentColor); 
  }
}

// Function to draw a circle at a specified point with a specified color
void circle(Point p, uint16_t c) {
  // Fill a circle at (p.x, p.y) with radius 5 and color c
  M5.Lcd.fillCircle(p.x, p.y, 5, c);
}
