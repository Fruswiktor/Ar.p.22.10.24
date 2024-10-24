/**
 * @file ColorDrawingApp.ino
 * @brief A touchscreen drawing application using the M5Tough display.
 * 
 * This application allows users to draw colored squares on a specified area
 * of the touchscreen. It includes three buttons for selecting colors and
 * resetting the drawing area. The color options include a default "RUBBER"
 * color (white) and an expanded palette of colors.
 *
 * ## Features:
 * - **RUBBER Button**: Sets the drawing color to white.
 * - **COLORS Button**: Cycles through an array of predefined colors.
 * - **RESET Button**: Clears the drawing area and resets the interface.
 *
 * ## Drawing Area:
 * The application defines a rectangular area where the user can draw squares
 * by tapping on the screen. The current color is displayed at the top of the screen.
 *
 * ## Dependencies:
 * - M5Tough library for touchscreen functionality.
 * - Arduino core library.
 *
 * ## Functions:
 * - `setup()`: Initializes the M5Tough display and buttons, setting up event handlers.
 * - `loop()`: Continuously checks for touch events and allows drawing within the area.
 * - `eventDisplayRUBBER()`: Handler for the RUBBER button to set the color to white.
 * - `eventDisplayCOLORS()`: Handler for the COLORS button to cycle through the color palette.
 * - `eventDisplayRESET()`: Handler for the RESET button to clear the screen and redraw.
 * - `isInsideDrawingArea()`: Checks if a given point lies within the drawing area.
 * - `drawSquare()`: Draws a colored square at a specified location on the screen.
 * - `displayCurrentColor()`: Updates the display to show the current drawing color.
 *
 * This code is designed for educational purposes and can be expanded with more features,
 * such as saving drawings or adding more color options.
 */

#include <M5Tough.h>  // Include the M5Tough library for touchscreen functionality
#include <Arduino.h>  // Include the Arduino core library

/**
 * @brief Color button definitions and settings.
 */
ButtonColors on_clrs = {GREEN, WHITE, WHITE};  
ButtonColors off_clrs = {BLACK, WHITE, WHITE};  

Button rubberButton(20, 200, 80, 40, false, "RUBBER", off_clrs, on_clrs, MC_DATUM); 
Button colorsButton(120, 200, 80, 40, false, "COLORS", off_clrs, on_clrs, MC_DATUM);
Button resetButton(220, 200, 80, 40, false, "RESET", off_clrs, on_clrs, MC_DATUM); 

/**
 * @brief Dimensions for the drawing area on the screen.
 */
const int drawingAreaX = 20;           
const int drawingAreaY = 20;           
const int drawingAreaWidth = 280;      
const int drawingAreaHeight = 160;     

/**
 * @brief Current drawing color and palette.
 */
uint16_t currentColor = WHITE;  // Default color is WHITE for "RUBBER"
uint16_t colorPalette[11] = {RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, 
                              ORANGE, PURPLE, PINK, LIGHTGREY, DARKGREY}; // Expanded color palette
const char* colorNames[11] = {"RED", "GREEN", "BLUE", "YELLOW", "MAGENTA", "CYAN", 
                                "ORANGE", "PURPLE", "PINK", "LIGHTGREY", "DARKGREY"}; // Expanded color names
int currentColorIndex = 0;  // Index for the current color in the palette

/**
 * @brief Initializes the M5Tough display and buttons.
 */
void setup() {
    M5.begin();  
    M5.Lcd.fillScreen(BLACK);  
    M5.Lcd.fillRect(drawingAreaX, drawingAreaY, drawingAreaWidth, drawingAreaHeight, WHITE);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextDatum(MC_DATUM);  
    M5.Buttons.draw();  

    // Add event handlers for button taps.
    rubberButton.addHandler(eventDisplayRUBBER, E_TAP);  
    colorsButton.addHandler(eventDisplayCOLORS, E_TAP);  
    resetButton.addHandler(eventDisplayRESET, E_TAP);  

    displayCurrentColor();  // Display the initial color.
}

/**
 * @brief Event handler for the "RUBBER" button tap.
 * 
 * @param e Event structure containing event data.
 */
void eventDisplayRUBBER(Event& e) {
    if (e.type == E_TAP) { 
        currentColor = WHITE;  
        displayCurrentColor();  // Update the displayed color.
    }
}

/**
 * @brief Event handler for the "COLORS" button tap.
 * 
 * @param e Event structure containing event data.
 */
void eventDisplayCOLORS(Event& e) {
    if (e.type == E_TAP) { 
        currentColorIndex = (currentColorIndex + 1) % 11;  // Cycle through the color palette
        currentColor = colorPalette[currentColorIndex];
        displayCurrentColor();  // Update the displayed color.
    }
}

/**
 * @brief Event handler for the "RESET" button tap.
 * 
 * @param e Event structure containing event data.
 */
void eventDisplayRESET(Event& e) {
    if (e.type == E_TAP) {  
        M5.Lcd.fillScreen(BLACK);  
        M5.Lcd.fillRect(drawingAreaX, drawingAreaY, drawingAreaWidth, drawingAreaHeight, WHITE);
        M5.Buttons.draw();  
        displayCurrentColor();  // Redisplay the current color after reset.
    }
}

/**
 * @brief Main loop of the program that handles drawing events.
 */
void loop() {
    M5.update();  

    Event& e = M5.Buttons.event;  

    // Check if the event is related to movement or tap
    if (e & (E_MOVE | E_GESTURE | E_TAP)) {
        if (isInsideDrawingArea(e.to)) {
            drawSquare(e.to, currentColor);  
        }
    }
}

/**
 * @brief Checks if a point is inside the drawing area.
 * 
 * @param p Point to check.
 * @return True if the point is inside the drawing area, false otherwise.
 */
bool isInsideDrawingArea(Point p) {
    return (p.x >= drawingAreaX && p.x <= drawingAreaX + drawingAreaWidth &&
            p.y >= drawingAreaY && p.y <= drawingAreaY + drawingAreaHeight);
}

/**
 * @brief Draws a square at the specified point with the given color.
 * 
 * @param p Point where the square is drawn.
 * @param c Color of the square.
 */
void drawSquare(Point p, uint16_t c) {
    int squareSize = 10;  
    M5.Lcd.fillRect(p.x - squareSize / 2, p.y - squareSize / 2, squareSize, squareSize, c);
}

/**
 * @brief Displays the current drawing color at the top of the screen.
 */
void displayCurrentColor() {
    // Clear the area where the color will be displayed
    M5.Lcd.fillRect(150, 0, 300, 20, BLACK);  

    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.drawString("Current Color: ", 100, 5);  // Move label slightly to the left
    M5.Lcd.setTextColor(currentColor);
    if (currentColor == WHITE) {
        M5.Lcd.drawString("RUBBER", 250, 5);  // Display current color for RUBBER
    } else {
        M5.Lcd.drawString(colorNames[currentColorIndex], 220, 5);  // Display current color name
        M5.Lcd.drawString(String(currentColorIndex + 1) + "/11", 350, 5);  // Display color index
    }
}
