#include "counter.h"

BoardA18::BoardA18() {
}
void BoardA18::init() {
  pinMode(pin_N_SELECT, OUTPUT);
  pinMode(pin_SHIFT, OUTPUT);
  pinMode(pin_DIGIT_A, INPUT);
  pinMode(pin_DIGIT_B, INPUT);
  pinMode(pin_DIGIT_C, INPUT);
  pinMode(pin_DIGIT_D, INPUT);

  digitalWrite(pin_N_SELECT, HIGH);
  digitalWrite(pin_SHIFT, HIGH);
}
void BoardA18::shift() {
  digitalWrite(pin_SHIFT, LOW);
  delayMicroseconds(10);
  digitalWrite(pin_SHIFT, HIGH);
}

int BoardA18::read_bcd(){
  int a = digitalRead(pin_DIGIT_A);
  int b = digitalRead(pin_DIGIT_B);
  int c = digitalRead(pin_DIGIT_C);
  int d = digitalRead(pin_DIGIT_D);

  int reading = 1 * a + 2 * b + 4 * c + 8 * d;
  //Serial.println(String(a) +","+ String(b) +","+ String(c) +"," +  String(d));
  //Serial.println("reading:" + String(reading));
  return reading;
}
uint64_t BoardA18::read() {
  
  uint64_t accumulator = 0;

  for (int cell = 0; cell <= 8; cell++) {

    //pin_N_SELECT correct register bank
    digitalWrite(pin_N_SELECT, cell == 0);
    delayMicroseconds(10);

    //store reading
    int reading = read_bcd();
    accumulator += pow(10, cell) * reading;
    //println64(&Serial, accumulator);

    //pin_SHIFT to next cell
    if (cell > 0) {
      shift();
    }
  }

  digitalWrite(pin_N_SELECT, HIGH); // restore counting

  return accumulator; // *2?
}