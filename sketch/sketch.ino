#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <iostream>
#include <map>

#define SCREEN_HEIGHT 64
#define SCREEN_WIDTH 128

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);

String output = "";
String outputDeci = "0";
String outputOct = "0";
String outputBin = "0";
String var1 = ": ";
String var2 = "";
String var3 = "";
String bases[3] = {"Decimal", "Binary", "Octal"};
int x = 0;
int base = 0;
boolean changed = true;


int minBases = 0;
int maxBases = 2;


void setup() {
  // put your setup code here, to run once:99
  Serial.begin(115200);
  Wire.begin(1, 2);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);

  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(42, INPUT_PULLUP);
  pinMode(41, INPUT_PULLUP);
  pinMode(40, INPUT_PULLUP);
  pinMode(39, INPUT_PULLUP);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Decimal <");
  display.println("Binary");
  display.println("Octal");
  display.display();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(4) == 0 && (base == 0)) {
    output = output + "9";
  } else if (digitalRead(5) == 0 && (base == 0)) {
    output = output + "8";
  } else if (digitalRead(6) == 0 && (base == 0 || base == 2)) {
    output = output + "7";
  } else if (digitalRead(7) == 0 && (base == 0 || base == 2)) {
    output = output + "6";
  } else if (digitalRead(15) == 0 && (base == 0 || base == 2)) {
    output = output + "5";
  } else if (digitalRead(16) == 0 && (base == 0 || base == 2)) {
    output = output + "4";
  } else if (digitalRead(17) == 0 && (base == 0 || base == 2)) {
    output = output + "3";
  } else if (digitalRead(18) == 0 && (base == 0 || base == 2)) {
    output = output + "2";
  } else if (digitalRead(8) == 0) {
    output = output + "1";
  } else if (digitalRead(3) == 0) {
    output = output + "0";
  } else if (digitalRead(41) == 0) {
    output.remove(output.length() - 1);
  }else if (digitalRead(42) == 0) {
    change();
  }else if (digitalRead(40) == 0) {
    changeBase(1);
  }else if (digitalRead(39) == 0) {
    changeBase(0);
  }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    //display.println(bases[x] + "< " + output);
    display.println(bases[0] + var1 + outputDeci);
    display.println(bases[1] + var2 + outputBin);
    display.println(bases[2] + var3 + outputOct);

    if (base == 0) {
      outputDeci = output;
      outputBin = "";
      outputOct = "";

      var1 = ": ";
      var2 = "";
      var3 = "";
      vars();
    }else if (base == 1) {
      outputDeci = "";
      outputBin = output;
      outputOct = "";

      var1 = "";
      var2 = ": ";
      var3 = "";
      vars();
    }else {
      outputDeci = "";
      outputBin = "";
      outputOct = output;

      var1 = "";
      var2 = "";
      var3 = ": ";
      vars();
    } 

    display.display();

  delay(40);
}

void changeBase(int y) {
  if(y == 0) {
    if(x != minBases){
      x--;
    }
  }else if(y == 1) {
    if(x != maxBases){
      x++;
    }
  }
}

void change() {
  int decimal = 0;
  int power = 1;
  int oldBase = base;
  base = x;

  if  (oldBase == 0) {
    if (base == 1) { //decimal to binary

    } else { //decimal to octal

    }
  } else if (oldBase == 1) {
    if (base == 0) { //binary to decimal

      for (int i = output.length() - 1; i >= 0; i--) {
        if (output[i] == '1') {
          decimal += power;
        }
        power *= 2;
      }

      output = decimal;
    } else { //binary to octal
      
    }
  } else {
    if (base == 0) { //octal to decimal
      for (int i = output.length(); i >= 0; i--) {
        decimal += (output[i] - '0') * power;
        power *= 8;
      }

      output = decimal;
    } else { //octal to binary
      
    }
  }
}

void vars() {
  if (x != base) {
    if (x == 0) {
      var1 = " <";
    }else if (x == 1) {
      var2 = " <";
    }else {
      var3 = " <";
    }
  }
}
