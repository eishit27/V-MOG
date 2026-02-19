#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal mylcd(rs, en, d4, d5, d6, d7);

int cooldown = 0;
int udelay = 3;       // (make sure to deal in whole numbers)
int framedelay = 250; // (250 would give us 4 frames per sec, 500 - 2 per sec, so on)
int cactus_position = 16;
// jump code
void jump(int count){
  mylcd.setCursor(0, 0);
  mylcd.write(byte (1));
  delay(framedelay);
  mylcd.setCursor(0, 0);
  mylcd.write(byte (0));
  delay(framedelay);
  count -= 1;
  if (count == 0){
    mylcd.setCursor(0, 0);
    mylcd.print(" ");
  } else {
    jump(count);
  }
  
// charecter "sprites" in byte arrays of 8
}
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
byte cactus[8] = {
  B00100,
  B01110,
  B11110,
  B01110,
  B01111,
  B01110,
  B11110,
  B01110
};

void setup() {
  Serial.begin(9600);
  pinMode(7,INPUT);
  mylcd.begin(16, 2);

  mylcd.createChar(0, dino_rightrun);
  mylcd.createChar(1, dino_leftrun);
  mylcd.createChar(2, cactus);

}

void loop() {
  if (digitalRead(7) == HIGH && cooldown == 0) { 
    mylcd.setCursor(0, 1);
    mylcd.print(" ");
    jump(udelay);
    cooldown = udelay*1; 
  }
  if (cooldown > 0){
    cooldown -= 1;
  }
  if(cactus_position > 1){
    cactus_position -= 1;
  }
  mylcd.setCursor(cactus_position, 1);
  mylcd.write(byte (2));
  mylcd.setCursor(cactus_position+1, 1);
  mylcd.print(" ");
  mylcd.setCursor(0, 1);
  mylcd.write(byte (0));
  delay(framedelay);
  mylcd.setCursor(0, 1);
  mylcd.write(byte (1));
  delay(framedelay);
  


}