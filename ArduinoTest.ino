// Import the libraries for the display

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Dimensions of the dispay
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

// Create the OLED object
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int humid, gas, humid_harm[3] = {875,950,1000}, gas_harm[3] = {125,500,750};

void setup() {
  pinMode(0,OUTPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.cp437(true);
}

void loop() {
  humid = analogRead(3);
  gas = analogRead(4);
  if ((humid>humid_harm[2])|(gas>gas_harm[2])){
    displayText("HIGH CONTAMINATION");
    digitalWrite(0,HIGH);
    delay(100);
    digitalWrite(0,LOW);
    delay(100);
  }
  else if ((humid>humid_harm[1])|(gas>gas_harm[1])){
    displayText("MEDIUM CONTAMINATION");
  }
  else if ((humid>humid_harm[0])|(gas>gas_harm[0])){
    displayText("LOW CONTAMINATION");
  }
  else{
    displayText("CLEAN AIR");
  }
}

void displayText(char text) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.write(text);
  display.display();
  delay(1000);
}
