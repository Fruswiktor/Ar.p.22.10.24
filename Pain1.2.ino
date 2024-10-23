/*
 * M5Tough Touchscreen Drawing Application
 *
 * This application allows users to draw on a touchscreen using two color buttons
 * (Red and Blue) and a reset button. Users can select a color and draw squares
 * on a designated drawing area by touching the screen. The reset button clears 
 * the drawing area. The application uses the M5Tough library for handling 
 * touchscreen input and button events.
 *
 * Features:
 * - Touchscreen interaction for drawing
 * - Color selection for drawing (Red and Blue)
 * - Clear drawing area with the Reset button
 *
 * Author: Frus
 * Date: 23.10.2024
 */


#include <M5Tough.h>  // Include the M5Tough library for touchscreen functionality
#include <Arduino.h>  // Include the Arduino core library

/** 
 * @brief Define button colors for on and off states.
 */
ButtonColors on_clrs = {GREEN, WHITE, WHITE};  
ButtonColors off_clrs = {BLACK, WHITE, WHITE};  

/** 
 * @brief Create buttons with specified properties.
 * 
 * Each button is initialized with its position, size, label, and color states.
 */
Button bl(20, 200, 80, 40, false, "RED", off_clrs, on_clrs, MC_DATUM); 
Button b2(120, 200, 80, 40, false, "BLUE", off_clrs, on_clrs, MC_DATUM);
Button b3(220, 200, 80, 40, false, "RESET", off_clrs, on_clrs, MC_DATUM); 

/** 
 * @brief Define dimensions of the drawing area.
 */
const int drawingAreaX = 20;           ///< X coordinate of the drawing area.
const int drawingAreaY = 20;           ///< Y coordinate of the drawing area.
const int drawingAreaWidth = 280;      ///< Width of the drawing area.
const int drawingAreaHeight = 160;     ///< Height of the drawing area.

uint16_t currentColor = RED;            ///< Variable to store the current drawing color.

/** 
 * @brief Setup function to initialize the device and UI components.
 * 
 * This function initializes the M5Tough device, sets up the display, 
 * creates buttons, and attaches event handlers for user interactions.
 */
void setup() {
    M5.begin();  // Initialize the M5Tough device.
    M5.Lcd.fillScreen(BLACK);  // Set the background color to black.
    M5.Lcd.fillRect(drawingAreaX, drawingAreaY, drawingAreaWidth, drawingAreaHeight, WHITE); // Draw the drawing area.
    M5.Lcd.setTextSize(2);  // Set the text size for buttons.
    M5.Lcd.setTextDatum(MC_DATUM);  // Set the text datum to center.
    M5.Buttons.draw();  // Draw buttons on the screen.

    // Add event handlers for button taps.
    bl.addHandler(eventDisplayBUTTON1, E_TAP);  
    b2.addHandler(eventDisplayBUTTON2, E_TAP);  
    b3.addHandler(eventDisplayBUTTON3, E_TAP);  
}

/** 
 * @brief Event handler for the RED button.
 * 
 * Changes the current drawing color to red when tapped.
 * 
 * @param e The event associated with the button tap.
 */
void eventDisplayBUTTON1(Event& e) {
    if (e.type == E_TAP) { 
        currentColor = RED;  
    }
}

/** 
 * @brief Event handler for the BLUE button.
 * 
 * Changes the current drawing color to blue when tapped.
 * 
 * @param e The event associated with the button tap.
 */
void eventDisplayBUTTON2(Event& e) {
    if (e.type == E_TAP) { 
        currentColor = BLUE;  
    }
}

/** 
 * @brief Event handler for the RESET button.
 * 
 * Clears the screen and redraws the drawing area when tapped.
 * 
 * @param e The event associated with the button tap.
 */
void eventDisplayBUTTON3(Event& e) {
    if (e.type == E_TAP) {  // Check if the event type is a tap.
        M5.Lcd.fillScreen(BLACK);  // Clear the entire screen.
        M5.Lcd.fillRect(drawingAreaX, drawingAreaY, drawingAreaWidth, drawingAreaHeight, WHITE); // Redraw the drawing area.
        M5.Buttons.draw();  // Redraw buttons on the screen.
    }
}

/** 
 * @brief Main loop to continuously check for events.
 */
void loop() {
    M5.update();  // Update the M5Tough state.

    Event& e = M5.Buttons.event;  // Reference the current button event.

    // Check for movement or gesture events.
    if (e & (E_MOVE | E_GESTURE | E_TAP)) {
        // If the event position is inside the drawing area, draw a square.
        if (isInsideDrawingArea(e.to)) {
            drawSquare(e.to, currentColor);  // Draw a square at the event location with the current color.
        }
    }
}

/** 
 * @brief Check if a point is inside the drawing area.
 * 
 * @param p The point to check.
 * @return True if the point is inside the drawing area, false otherwise.
 */
bool isInsideDrawingArea(Point p) {
    return (p.x >= drawingAreaX && p.x <= drawingAreaX + drawingAreaWidth &&
            p.y >= drawingAreaY && p.y <= drawingAreaY + drawingAreaHeight); // Return true if inside.
}

/** 
 * @brief Draw a square at a given point with a specified color.
 * 
 * @param p The point at which to draw the square.
 * @param c The color of the square.
 */
void drawSquare(Point p, uint16_t c) {
    int squareSize = 10;  // Define the size of the square.
    M5.Lcd.fillRect(p.x - squareSize / 2, p.y - squareSize / 2, squareSize, squareSize, c); // Draw the square centered at the point.
}
