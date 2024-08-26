#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
int echo = 6;
int trig = 7;
int ldr = 8;
Servo s1;  //9
Servo s2;  //10
int led = 13;
long timeinmicro;
long distance;
int state = 0;
int clear = 0;
int gate1 = 0;
int gate2 = 0;
int gatestate = 0;
int vis_in = 0;
int vis_out = 0;
const int max_in = 5;
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  pinMode(6, INPUT);
  s1.attach(9);
  s2.attach(10);
  s1.write(0);
  s2.write(0);
  pinMode(ldr, INPUT);
  pinMode(led, OUTPUT);
  lcd.begin();
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  timeinmicro = pulseIn(echo, HIGH);
  distance = timeinmicro / 29 / 2;
  Serial.println(distance);
  if (state == 0) {
    if (clear == 1) {
      lcd.clear();
      clear = 0;
    }
    lcd.print("    SLOTS:");
    lcd.print(max_in - vis_in + vis_out);
    lcd.setCursor(2, 1);
    lcd.print("IN:");
    lcd.print(vis_in);
    lcd.setCursor(9, 1);
    lcd.print("OUT:");
    lcd.print(vis_out);
  }
  delay(10);

  if (distance > 0 && distance < 10 && gate2 == 0 && gatestate == 0) {
    if (digitalRead(ldr) != 1) {
      digitalWrite(led, HIGH);
    }
    if (state == 1)
      clear = 1;
    if ((max_in - vis_in + vis_out) == 0) {
      state = 1;
      if (clear != 1)
        lcd.clear();
      lcd.print(" PARKING FULL!!");
      lcd.setCursor(0, 1);
      lcd.print("  GO ELSEWHERE");
      gatestate = 1;
    } else {
      for (int i = 0; i <= 90; i++) {
        s1.write(i);
        delay(15);
      }
      gate1 = 1;
      gatestate = 1;
      vis_in++;
    }
  } else if (distance > 10 && distance < 20 && gate1 == 0 && gatestate == 0) {
    if (digitalRead(ldr) != 1) {
      digitalWrite(led, HIGH);
    }
    if (state == 2)
      clear = 1;
    state = 2;
    if ((max_in - vis_in + vis_out) == 5) {

      if (clear != 1)
        lcd.clear();
      lcd.print("INVALID");
      lcd.setCursor(0, 1);
      lcd.print("INVALID");
      gate2 = 1;
      gatestate = 1;
      for (int i = 0; i <= 90; i++) {
        s2.write(i);
        delay(15);
      }
    } else {
      if (clear != 1)
        lcd.clear();
      lcd.print("   THANK-YOU");
      lcd.setCursor(0, 1);
      lcd.print(" PLS COME AGAIN");
      for (int i = 0; i <= 90; i++) {
        s2.write(i);
        delay(15);
      }
      gate2 = 1;
      gatestate = 1;
      vis_out++;
    }
  } else if (gatestate == 1 && distance > 20) {
    delay(200);
    if (gate1) {
      for (int i = 90; i >= 0; i--) {
        s1.write(i);
        delay(15);
      }
    } else if (gate2) {
      for (int i = 90; i >= 0; i--) {
        s2.write(i);
        delay(15);
      }
    }
    digitalWrite(led, LOW);
    gate1 = 0;
    gate2 = 0;
    gatestate = 0;
    state = 0;
    clear = 1;
  }
  Serial.println(digitalRead(ldr));
}