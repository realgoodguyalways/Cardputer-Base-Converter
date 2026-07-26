#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_HEIGHT 64
#define SCREEN_WIDTH 128

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin(1, 2);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);

  pinMode(5, INPUT_PULLUP);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("hello World");
  display.display();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  delay(1000); // this speeds up the simulation
}
