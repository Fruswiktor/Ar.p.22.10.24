#include <M5Tough.h>

ButtonColors on_clrs = {BLUE, WHITE, WHITE};
ButtonColors off_clrs = {BLACK, WHITE, WHITE};
Button bl(20, 200, 80, 40, false, "RED", off_clrs, on_clrs, MC_DATUM);
Button b2(120, 200, 80, 40, false, "BLUE", off_clrs, on_clrs, MC_DATUM);
Button b3(220, 200, 80, 40, false, "RESET", off_clrs, on_clrs, MC_DATUM);

void eventDisplay(Event& e) {
  M5.Lcd.fillRect(0, 0, 320, 150, BLACK);
  Serial.printf("%-12s finger%d  %-18s (%3d, %3d) --> (%3d, %3d)   ",
                e.typeName(), e.finger, e.objName(), e.from.x, e.from.y,
                e.to.x, e.to.y);

  Serial.printf("( dir %d deg, dist %d, %d ms )\r\n", e.direction(),
                e.distance(), e.duration);
}

void setup() {
  M5.begin();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextDatum(MC_DATUM);
  M5.Buttons.draw();
  bl.addHandler(eventDisplay, E_ALL);
  b2.addHandler(eventDisplay, E_ALL);
  b3.addHandler(eventDisplay, E_ALL);
}

void loop() {
  M5.update();
  Event& e = M5.Buttons.event;
  if (e & (E_MOVE | E_RELEASE)) circle(e & E_MOVE ? e.from : e.to, BLACK);
  if (e & (E_TOUCH | E_MOVE)) circle(e.to, e.finger ? BLUE : RED);



  
}

void circle(Point p, uint16_t c) {
  M5.Lcd.fillCircle(p.x, p.y, 4, c);
  M5.Lcd.drawCircle(p.x, p.y, 5, c);
}

