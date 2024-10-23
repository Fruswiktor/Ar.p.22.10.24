#include <M5Tough.h>
#include <Arduino.h>

ButtonColors on_clrs = {GREEN, WHITE, WHITE};
ButtonColors off_clrs = {BLACK, WHITE, WHITE};
Button bl(20, 200, 80, 40, false, "RED", off_clrs, on_clrs, MC_DATUM);
Button b2(120, 200, 80, 40, false, "BLUE", off_clrs, on_clrs, MC_DATUM);
Button b3(220, 200, 80, 40, false, "RESET", off_clrs, on_clrs, MC_DATUM);

uint16_t currentColor = RED;  // Zmienna do przechowywania aktualnego koloru

void setup() {
  M5.begin();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextDatum(MC_DATUM);
  M5.Buttons.draw();
  bl.addHandler(eventDisplayBUTTON1, E_TAP);
  b2.addHandler(eventDisplayBUTTON2, E_TAP);
  b3.addHandler(eventDisplayBUTTON3, E_TAP);
}

void eventDisplayBUTTON1(Event& e) {
  // Zmiana koloru na czerwony
  if (e.type == E_TAP) {
    currentColor = RED;  // Aktualizacja koloru
  }
}

void eventDisplayBUTTON2(Event& e) {
  // Zmiana koloru na niebieski
  if (e.type == E_TAP) {
    currentColor = BLUE;  // Aktualizacja koloru
  }
}

void eventDisplayBUTTON3(Event& e) {
  // Resetowanie programu
  ESP.restart();
}

void loop() {
  M5.update();

  Event& e = M5.Buttons.event;
  
  // Rysowanie kółek natychmiast w odpowiedzi na ruch lub gest
  if (e & (E_MOVE | E_GESTURE)) circle(e.to, currentColor); 
}

void circle(Point p, uint16_t c) {
  M5.Lcd.fillCircle(p.x, p.y, 5, c);
}
