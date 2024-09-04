#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64


int counter=0;
String dir="";
unsigned long last_run=0;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(3), shaft_moved, FALLING);
  pinMode(4, INPUT);
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))  {
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }
  display.clearDisplay();
  display.setTextColor(WHITE);

}

void shaft_moved()  {
  if (millis()-last_run>5)  {
    if (digitalRead(4)==1)  {
      if (counter<25) { 
        counter++;
        dir="CW";
      }
    }
    
    if (digitalRead(4)==0)  {
      if (counter>-25)  {
        counter--;
        dir="CCW";
      }
    }
    last_run= millis();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  display.setCursor(64,32);
  display.clearDisplay();
  display.display();
  display.println(counter);
  display.display();
}
