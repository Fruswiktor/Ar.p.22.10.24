/*
 * M5Tough Painting Application
 * 
 * This application leverages the M5Tough library to create a simple
 * graphical interface on the M5Tough device. It features three buttons 
 * for color selection (RED or BLUE) and a reset function.
 * 
 * Button Functionalities:
 * - Button 1 ("RED"): Sets the current drawing color to RED when pressed.
 * - Button 2 ("BLUE"): Sets the current drawing color to BLUE when pressed.
 * - Button 3 ("RESET"): Restarts the ESP32 device when pressed.
 * 
 * The display is initialized with a black background, and buttons are 
 * rendered with defined colors for their active and inactive states.
 * 
 * Ensure the M5Tough library is properly included and configured for this 
 * code to work correctly.
 */

#include <M5Tough.h>
#include <Arduino.h>

// Define button colors for their active (on) and inactive (off) states.
ButtonColors on_clrs = {GREEN, WHITE, WHITE}; // Active state colors
ButtonColors off_clrs = {BLACK, WHITE, WHITE}; // Inactive state colors

// Create button instances with specified position, size, label, and color states.
Button bl(20, 200, 80, 40, false, "RED", off_clrs, on_clrs, MC_DATUM);  // RED button
Button b2(120, 200, 80, 40, false, "BLUE", off_clrs, on_clrs, MC_DATUM); // BLUE button
Button b3(220, 200, 80, 40, false, "RESET", off_clrs, on_clrs, MC_DATUM); // RESET button

// Variable to hold the currently selected color.
uint16_t currentColor = RED; // Default color set to RED

/**
 * @brief Initializes the M5Tough device and sets up the display.
 */
void setup() {
  M5.begin(); // Initialize the M5Tough hardware
  M5.Lcd.fillScreen(BLACK); // Set the screen background to black
  M5.Lcd.setTextSize(2); // Set the text size for display
  M5.Lcd.setTextDatum(MC_DATUM); // Center text for button labels
  M5.Buttons.draw(); // Render buttons on the screen

  // Attach event handlers for button press events
  bl.addHandler(eventDisplayBUTTON1, E_TAP); // RED button event
  b2.addHandler(eventDisplayBUTTON2, E_TAP); // BLUE button event
  b3.addHandler(eventDisplayBUTTON3, E_TAP); // RESET button event
}

/**
 * @brief Event handler for the RED button.
 * 
 * Sets the current drawing color to RED when the button is tapped.
 *
 * @param e The event object containing event details.
 */
void eventDisplayBUTTON1(Event& e) {
  if (e.type == E_TAP) { // Check if the event is a tap
    currentColor = RED; // Update current color to RED
  }
}

/**
 * @brief Event handler for the BLUE button.
 * 
 * Sets the current drawing color to BLUE when the button is tapped.
 *
 * @param e The event object containing event details.
 */
void eventDisplayBUTTON2(Event& e) {
  if (e.type == E_TAP) { // Check if the event is a tap
    currentColor = BLUE; // Update current color to BLUE
  }
}

/**
 * @brief Event handler for the RESET button.
 * 
 * Restarts the ESP32 device when the button is tapped.
 *
 * @param e The event object containing event details.
 */
void eventDisplayBUTTON3(Event& e) {
  ESP.restart(); // Restart the ESP32 device
}

/**
 * @brief Main loop that handles button events and drawing on the screen.
 */
void loop() {
  M5.update(); // Update the state of the M5Tough device

  Event& e = M5.Buttons.event; // Reference to the current button event

  // Check if the event indicates a movement or gesture
  if (e & (E_MOVE | E_GESTURE)) {
    circle(e.to, currentColor); // Draw a circle at the touch position with the selected color
  }
}

/**
 * @brief Draws a filled circle at a specified point with a specified color.
 * 
 * @param p The point where the circle should be drawn.
 * @param c The color of the circle.
 */
void circle(Point p, uint16_t c) {
  M5.Lcd.fillCircle(p.x, p.y, 5, c); // Draw a circle with radius 5 at the specified point
}
