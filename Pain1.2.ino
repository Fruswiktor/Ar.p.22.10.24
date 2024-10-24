#include <M5Tough.h>  // Include the M5Tough library for touchscreen functionality
#include <Arduino.h>  // Include the Arduino core library

ButtonColors on_clrs = {GREEN, WHITE, WHITE};  
ButtonColors off_clrs = {BLACK, WHITE, WHITE};  

Button rubberButton(20, 200, 80, 40, false, "RUBBER", off_clrs, on_clrs, MC_DATUM); 
Button colorsButton(120, 200, 80, 40, false, "COLORS", off_clrs, on_clrs, MC_DATUM);
Button resetButton(220, 200, 80, 40, false, "RESET", off_clrs, on_clrs, MC_DATUM); 

const int drawingAreaX = 20;           
const int drawingAreaY = 20;           
const int drawingAreaWidth = 280;      
const int drawingAreaHeight = 160;     

uint16_t currentColor = WHITE;  // Default color is now WHITE for "RUBBER"
uint16_t colorPalette[11] = {RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, 
                              ORANGE, PURPLE, PINK, LIGHTGREY, DARKGREY}; // Expanded color palette
const char* colorNames[11] = {"RED", "GREEN", "BLUE", "YELLOW", "MAGENTA", "CYAN", 
                                "ORANGE", "PURPLE", "PINK", "LIGHTGREY", "DARKGREY"}; // Expanded color names
int currentColorIndex = 0;  // Index for the current color in the palette

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

void eventDisplayRUBBER(Event& e) {
    if (e.type == E_TAP) { 
        currentColor = WHITE;  
        displayCurrentColor();  // Update the displayed color.
    }
}

void eventDisplayCOLORS(Event& e) {
    if (e.type == E_TAP) { 
        currentColorIndex = (currentColorIndex + 1) % 11;  // Cycle through the color palette
        currentColor = colorPalette[currentColorIndex];
        displayCurrentColor();  // Update the displayed color.
    }
}

void eventDisplayRESET(Event& e) {
    if (e.type == E_TAP) {  
        M5.Lcd.fillScreen(BLACK);  
        M5.Lcd.fillRect(drawingAreaX, drawingAreaY, drawingAreaWidth, drawingAreaHeight, WHITE);
        M5.Buttons.draw();  
        displayCurrentColor();  // Redisplay the current color after reset.
    }
}

void loop() {
    M5.update();  

    Event& e = M5.Buttons.event;  

    if (e & (E_MOVE | E_GESTURE | E_TAP)) {
        if (isInsideDrawingArea(e.to)) {
            drawSquare(e.to, currentColor);  
        }
    }
}

bool isInsideDrawingArea(Point p) {
    return (p.x >= drawingAreaX && p.x <= drawingAreaX + drawingAreaWidth &&
            p.y >= drawingAreaY && p.y <= drawingAreaY + drawingAreaHeight);
}

void drawSquare(Point p, uint16_t c) {
    int squareSize = 10;  
    M5.Lcd.fillRect(p.x - squareSize / 2, p.y - squareSize / 2, squareSize, squareSize, c);
}

/** 
 * @brief Display the current drawing color at the top of the screen.
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
