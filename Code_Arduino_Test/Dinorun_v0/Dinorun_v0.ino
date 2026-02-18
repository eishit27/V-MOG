#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal mylcd(rs, en, d4, d5, d6, d7);

// 1. Define the custom character arrays
byte dino_rightrun[8] = {
  B11110,
  B01011,
  B01111,
  B01100,
  B01111,
  B11100,
  B00100,
  B01000
};
byte dino_leftrun[8] = {
  B11110,
  B01011,
  B01111,
  B01100,
  B01111,
  B11100,
  B01000,
  B00100
};

void jump(int count){
  mylcd.setCursor(0, 0);
  mylcd.write(byte (1));
  delay(100);
  mylcd.setCursor(0, 0);
  mylcd.write(byte (0));
  delay(100);
  count -= 1;
  if (count == 0){
    mylcd.setCursor(0, 0);
    mylcd.print(" ");
  } else {
    jump(count);
  }
  
}

void setup() {
  Serial.begin(9600);
  //pinMode(7,INPUT);
  mylcd.begin(16, 2);

  // 2. Register the character to slot 0 (can be 0-7)
  mylcd.createChar(0, dino_rightrun);
  mylcd.createChar(1, dino_leftrun);
  // 3. Print it!
  
  // To print custom characters, you use write() instead of print()
}

void loop() {
  if (Serial.available() > 0) {
    char key = Serial.read();
    if (key == 'w' || key == 'W') {
      mylcd.setCursor(0, 1);
      mylcd.print(" ");
      jump(3);
    }
  }
  delay(100);
  mylcd.setCursor(0, 1);
  mylcd.write(byte (0));
  delay(100);
  mylcd.setCursor(0, 1);
  mylcd.write(byte (1));
  delay(100);
  
    

}