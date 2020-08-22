#include <Rotary.h>
#include <Keyboard.h>

// Untuk pinout rotary encoder berbeda - beda silahkan cek datasheetnya
Rotary rotary = Rotary(2, 3);

int counter = 0;
int Sumbu_X = 4;
int Sumbu_Y = 5;
int Sumbu_Z = 6;

int buttonStateX = 0; 
int buttonStateY = 0; 
int buttonStateZ = 0; 

int buttonLast = 0;

void setup() {
  Serial.begin(57600);
  Keyboard.begin();
  pinMode(4, INPUT_PULLUP); 
  pinMode(5, INPUT_PULLUP); 
  pinMode(6, INPUT_PULLUP); 
  attachInterrupt(0, rotate, CHANGE);
  attachInterrupt(1, rotate, CHANGE);
}

void loop() {
  
}

// rotate is called anytime the rotary inputs change state.
void rotate() {
  unsigned char result = rotary.process();

  // Tombol Untuk Sumbu X, Y dan Z
  buttonStateX = digitalRead(Sumbu_X);
  buttonStateY = digitalRead(Sumbu_Y);
  buttonStateZ = digitalRead(Sumbu_Z);
  if (buttonStateX == LOW) {buttonLast = 0;}
  else if (buttonStateY == LOW) {buttonLast = 1;}
  else if (buttonStateZ == LOW) {buttonLast = 2;}
  switch (buttonLast) {
    case 0:    // Tombol Klik Kiri Mouse
      if (result == DIR_CW) {
      Keyboard.write(KEY_LEFT_ARROW);
      } else if (result == DIR_CCW) {
      Keyboard.write(KEY_RIGHT_ARROW);
    }
      break;
    case 1:    // Tombol Klik Kanan Mouse
      if (result == DIR_CW) {
      Keyboard.write(KEY_UP_ARROW);
      } else if (result == DIR_CCW) {
      Keyboard.write(KEY_DOWN_ARROW);
    }
      break;
    case 2:    // Tombol Klik Tengah Mouse
     if (result == DIR_CW) {
      Keyboard.write(KEY_PAGE_UP);
      } else if (result == DIR_CCW) {
      Keyboard.write(KEY_PAGE_DOWN);
    }
      break;
  delay(1); 
  }
}
