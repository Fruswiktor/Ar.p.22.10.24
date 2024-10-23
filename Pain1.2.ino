#include <M5Tough.h>  // Include the M5Tough library for touchscreen functionality
#include <Arduino.h>  // Include the Arduino core library

ButtonColors on_clrs = {GREEN, WHITE, WHITE};  
ButtonColors off_clrs = {BLACK, WHITE, WHITE};  

Button bl(20, 200, 80, 40, false, "RED", off_clrs, on_clrs, MC_DATUM); 
Button b2(120, 200, 80, 40, false, "BLUE", off_clrs, on_clrs, MC_DATUM);
Button b3(220, 200, 80, 40, false, "RESET", off_clrs, on_clrs, MC_DATUM); 

const int drawingAreaX = 20;           
const int drawingAreaY = 20;           
const int drawingAreaWidth = 280;      
const int drawingAreaHeight = 160;     

uint16_t currentColor = RED;            ///< Variable to store the current drawing color.

void setup() {
    M5.begin();  
    M5.Lcd.fillScreen(BLACK);  
    M5.Lcd.fillRect(drawingAreaX, drawingAreaY, drawingAreaWidth, drawingAreaHeight, WHITE);
    M5.Lcd.setTextSize(1);  // Zmniejsz rozmiar tekstu
    M5.Lcd.setTextDatum(MC_DATUM);  
    M5.Buttons.draw();  

    // Add event handlers for button taps.
    bl.addHandler(eventDisplayBUTTON1, E_TAP);  
    b2.addHandler(eventDisplayBUTTON2, E_TAP);  
    b3.addHandler(eventDisplayBUTTON3, E_TAP);  

    displayCurrentColor();  // Display the initial color.
}

void eventDisplayBUTTON1(Event& e) {
    if (e.type == E_TAP) { 
        currentColor = RED;  
        displayCurrentColor();  // Update the displayed color.
    }
}

void eventDisplayBUTTON2(Event& e) {
    if (e.type == E_TAP) { 
        currentColor = BLUE;  
        displayCurrentColor();  // Update the displayed color.
    }
}

void eventDisplayBUTTON3(Event& e) {
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
    // Wyczyść obszar, w którym będzie wyświetlany kolor
    M5.Lcd.fillRect(150, 0, 300, 20, BLACK);  // Zmodyfikuj wymiary, jeśli to konieczne

    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.drawString("Current Color: ", 150, 5);  // Display label
    if (currentColor == RED) {
        M5.Lcd.setTextColor(RED);
        M5.Lcd.drawString("RED", 250, 5);  // Display current color
    } else {
        M5.Lcd.setTextColor(BLUE);
        M5.Lcd.drawString("BLUE", 250, 5);  // Display current color
    }
}
