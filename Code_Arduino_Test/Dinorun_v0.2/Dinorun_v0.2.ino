#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal mylcd(rs, en, d4, d5, d6, d7);

// Time tracking
unsigned long lastFrameTime = 0;
unsigned long lastCactusTime = 0;
unsigned long jumpStartTime = 0;
unsigned long coolDown = 0;
// Game Settings
int framedelay = 200;    
int cactusSpeed = 250;   
int cactus_position = 15;
bool isJumping = false;
bool dinoFrame = 0;

byte dino_rightrun[8] = { B11110, B01011, B01111, B01100, B01111, B11100, B00100, B01000 };
byte dino_leftrun[8]  = { B11110, B01011, B01111, B01100, B01111, B11100, B01000, B00100 };
byte cactusSprite[8]  = { B00100, B01110, B11110, B01110, B01111, B01110, B11110, B01110 };

void setup() {
  pinMode(7, INPUT); // Ensure your button/wire is connected to Pin 7
  mylcd.begin(16, 2);
  mylcd.createChar(0, dino_rightrun);
  mylcd.createChar(1, dino_leftrun);
  mylcd.createChar(2, cactusSprite);
}

void loop() {
  unsigned long currentTime = millis();

  // --- 1. PHYSICAL TRIGGER (Pin 7) ---
  if (digitalRead(7) == HIGH && !isJumping && (coolDown == 0)) {
    isJumping = true;
    jumpStartTime = currentTime;
    coolDown = 1000;
    // Clear ground position immediately so we don't have two Dinos
    mylcd.setCursor(0, 1);
    mylcd.print(" "); 
  }

  // --- 2. JUMP STATE MANAGEMENT ---
  if (isJumping) {
    // If less than 700ms has passed, stay in the air
    if (currentTime - jumpStartTime < 700) { 
      mylcd.setCursor(0, 0);
      mylcd.write(byte(dinoFrame)); 
    } else {
      // Time's up: Fall down
      isJumping = false;
      mylcd.setCursor(0, 0); 
      mylcd.print(" "); // Clear the air
    }
  }

  // --- 3. DINO ANIMATION (Legs) ---
  if (currentTime - lastFrameTime >= framedelay) {
    lastFrameTime = currentTime;
    dinoFrame = !dinoFrame; 
    if(coolDown >0){
      coolDown -= 100;
    }
    if (!isJumping) {
      mylcd.setCursor(0, 1);
      mylcd.write(byte(dinoFrame));
    }
  }

  // --- 4. CACTUS MOVEMENT ---
  if (currentTime - lastCactusTime >= cactusSpeed) {
    lastCactusTime = currentTime;
    
    // Erase the tail of the cactus
    mylcd.setCursor(cactus_position, 1);
    mylcd.print(" ");
    
    cactus_position--;
    
    // If it goes off screen, reset to right side
    if (cactus_position < 0) {
      cactus_position = 15;
    }

    // Draw Cactus at new position
    mylcd.setCursor(cactus_position, 1);
    mylcd.write(byte(2));

    // --- 5. COLLISION DETECTION ---
    // If cactus is at index 0 and dino is NOT in the air
    if (cactus_position == 0 && !isJumping) {
      mylcd.clear();
      mylcd.setCursor(3, 0);
      mylcd.print("GAME OVER!");
      // Infinite loop to freeze game on death
      while(1); 
    }
  }
}