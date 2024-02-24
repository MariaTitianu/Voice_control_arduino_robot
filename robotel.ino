#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_MODULE
#include <Dabble.h>
// Pinii motor 1
#define mpin00 5
#define mpin01 6
// Pinii motor 2
#define mpin10 9
#define mpin11 10
bool dataflag = 0;
String Serialdata = "";

void setup() {
  // configurarea pinilor motor ca iesire, initial valoare 0

  Serial.begin(9600);
  Dabble.begin(9600);
  digitalWrite(mpin00, 0);
  digitalWrite(mpin01, 0);
  digitalWrite(mpin10, 0);
  digitalWrite(mpin11, 0);
  pinMode(mpin00, OUTPUT);
  pinMode(mpin01, OUTPUT);
  pinMode(mpin10, OUTPUT);
  pinMode(mpin11, OUTPUT);
}
// Functie pentru controlul unui motor
// Intrare: pinii m1 si m2, directia si viteza
void StartMotor(int m1, int m2, int forward, int speed) {
  if (speed == 0)  // oprire
  {
    digitalWrite(m1, 0);

    digitalWrite(m2, 0);
  } else {
    if (forward) {
      digitalWrite(m2, 0);
      analogWrite(m1, speed);  // folosire PWM
    } else {
      digitalWrite(m1, 0);
      analogWrite(m2, speed);
    }
  }
}
// Functie de siguranta
// Executa oprire motoare, urmata de delay
void delayStopped(int ms) {
  StartMotor(mpin00, mpin01, 0, 0);
  StartMotor(mpin10, mpin11, 0, 0);
  delay(ms);
}

void loop() {

  Dabble.processInput();
  // Acum se pornesc motoarele DC
  if (Terminal.available()) {
    Serialdata = "";
    while (Terminal.available() != 0) {
      Serialdata += Terminal.read();
    }
    Serialdata.toLowerCase();
    if (Serialdata.equals("forward") || Serialdata.equals("fata")) {
      StartMotor(mpin00, mpin01, 0, 255);
      StartMotor(mpin10, mpin11, 0, 255);
      delay(1000);
    } else if (Serialdata.equals("back") || Serialdata.equals("spate")) {
      StartMotor(mpin00, mpin01, 1, 255);
      StartMotor(mpin10, mpin11, 1, 255);
      delay(1000);
    } else if (Serialdata.equals("left") || Serialdata.equals("stanga")) {
      StartMotor(mpin00, mpin01, 0, 255);
      StartMotor(mpin10, mpin11, 1, 255);
      delay(1000);
    } else if (Serialdata.equals("right") || Serialdata.equals("dreapta")) {

      StartMotor(mpin00, mpin01, 1, 255);
      StartMotor(mpin10, mpin11, 0, 255);
      delay(1000);
    } else if (Serialdata.equals("stop")) {
      delayStopped(500);
    }
  }
}