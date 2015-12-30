#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

#define LED_SIZE 128

int enables[3] = {true, true, false};
int drivers[3] = {0x70, 0x71, 0x72};
int brightnesses[3] = {0, 0, 0};

int mode = 0;
String numberString = "";
int numbers[LED_SIZE*3] = {};
int counter = -1;

Adafruit_8x16matrix matrixes[3] = {
  Adafruit_8x16matrix(),
  Adafruit_8x16matrix(),
  Adafruit_8x16matrix()
};

void setup() {
  Serial.begin(115200);

  if(enables[0]){
    matrixes[0].begin(drivers[0]);
    matrixes[0].setBrightness(brightnesses[0]);
  }
  
  if(enables[1]){
    matrixes[1].begin(drivers[1]);
    matrixes[1].setBrightness(brightnesses[1]);
  }
  
  if(enables[2]){
    matrixes[2].begin(drivers[2]);
    matrixes[2].setBrightness(brightnesses[2]);
  }
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    int il = sizeof(input);
    
//    Serial.print("input: " + String(input));
//    Serial.println(", " + String(input - '0'));
//    Serial.println("input length: " + String(il));
    
    for(int i = 0; i < il; i++){
      char c = input;
      int ctoi = input - '0';

      if(c == 'H'){
        mode = 11;
        numbers[counter] += numberString.toInt() + 1;
        numberString = "";
        counter++;
      }
      else if(c == '/'){
        mode = 19;
        numbers[counter] += numberString.toInt() + 1;
        numberString = "";
      }
      // numeric
      else if(int(ctoi) >= 0 && int(ctoi) <= 9){
        if(mode == 11){
          numberString += String(c);
        }
        else if(mode == 19){
          // end
//          Serial.println("///end");
          memset( numbers, 0, sizeof(numbers) );
          counter = -1;
          mode = 0;
        }
      }
    }

    if(mode == 19){
      int nl = sizeof(numbers) / sizeof(numbers[0]);
//      Serial.println("numbers length: " + String(nl));
//      Serial.println("counter: " + String(counter));
//      Serial.println("mode: " + String(mode));

      
      if(enables[0]) matrixes[0].clear();
      if(enables[1]) matrixes[1].clear();
      if(enables[2]) matrixes[2].clear();

      int numberCount = 0;
      for(int i = 0; i < nl; i++){
        int n = numbers[i];
        if(n > 0){
          n -= 1;
          int y = 0;
          int x = 0;
//          Serial.println(String(n));
          
          if(n < LED_SIZE){
            y = floor(n / 8);
            x = n - (floor(n / 8) * 8);
//            Serial.println("01:" + String(n) + ", x:" + String(x) + ", y:" + String(y) );
            if(enables[0]) matrixes[0].drawPixel(x, y, LED_ON);
          }
          else if(n < LED_SIZE * 2){
            n -= LED_SIZE;
            y = floor(n / 8);
            x = n - (floor(n / 8) * 8);
//            Serial.println("02:" + String(n) + ", x:" + String(x) + ", y:" + String(y) );
            if(enables[1]) matrixes[1].drawPixel(x, y, LED_ON);
          }
          else if(n < LED_SIZE * 3){
            n -= LED_SIZE * 2;
            y = floor(n / 8);
            x = n - (floor(n / 8) * 8);
//            Serial.println("03:" + String(n) + ", x:" + String(x) + ", y:" + String(y) );
            if(enables[2]) matrixes[2].drawPixel(x, y, LED_ON);
          }
          numberCount++;
//          Serial.println("");
        }
      }

      if(numberCount > 0){
      }
      
      if(enables[0]) matrixes[0].writeDisplay();
      if(enables[1]) matrixes[1].writeDisplay();
      if(enables[2]) matrixes[2].writeDisplay();
    }

//    Serial.println("");
  }
}


