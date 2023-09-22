#include "band_filter.h"

BoardA10::BoardA10() {
}

void BoardA10::init() {
  pinMode(pin_N_BAND_INC, OUTPUT);
  pinMode(pin_N_BAND_ZERO, OUTPUT);

  digitalWrite(pin_N_BAND_ZERO, HIGH);
  digitalWrite(pin_N_BAND_INC, HIGH);
}

void BoardA10::increment() {
  digitalWrite(pin_N_BAND_INC, LOW);
  delayMicroseconds(10);
  digitalWrite(pin_N_BAND_INC, HIGH);
  band++;
}

void BoardA10::reset() {
  digitalWrite(pin_N_BAND_ZERO, LOW);
  delayMicroseconds(10);
  digitalWrite(pin_N_BAND_ZERO, HIGH);
  band = 0;
}

void BoardA10::set(int filter_index) {
  if (filter_index != band) {
    reset();
    for (int index = 0; index < filter_index; index++) {
      increment();
    }
    delay(1); //system settling
    //Serial.println("band set to : " + String(band));
  }
}