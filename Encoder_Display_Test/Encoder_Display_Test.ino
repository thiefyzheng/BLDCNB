#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

int counter = 0;
int current = counter;
String dir = "";
unsigned long last_run = 0;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  attachInterrupt(digitalPinToInterrupt(3), shaft_moved, FALLING);
  pinMode(4, INPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;);
  }
  display.setTextSize(5);
  display.setCursor(32, 16);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.println(counter);
  display.display();
}

void shaft_moved() {
  if (millis() - last_run > 5) {
    if (digitalRead(4) == 1) {
      if (counter < 25) {
        counter++;
        dir = "CW";
      }
    } else {
      if (counter > -25) {
        counter--;
        dir = "CCW";
      }
    }
    last_run = millis();
  }
}

void loop() {
  display.setCursor(32, 16);
  if (counter != current) {
    display.clearDisplay();
    display.display();
    display.println(counter);
    display.display();
    current = counter;
  }
}
