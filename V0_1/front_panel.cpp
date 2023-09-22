#include "front_panel.h"

BoardA19::BoardA19() {
}

void BoardA19::init() {
  pinMode(pin_MANUAL, INPUT);
  pinMode(pin_N_BAND_SELECT, INPUT);
  pinMode(pin_EIGHTY, INPUT);
  pinMode(pin_CHECK, INPUT);
  pinMode(pin_RES_A, INPUT);
  pinMode(pin_RES_B, INPUT);
  pinMode(pin_RES_C, INPUT);
}

bool BoardA19::band_automatic() {
  return !digitalRead(pin_MANUAL);
}
bool BoardA19::band_button_pressed() {
  return !digitalRead(pin_N_BAND_SELECT);
}

bool BoardA19::input_high_range() {
  return !digitalRead(pin_EIGHTY);
}
bool BoardA19::input_check() {
  return digitalRead(pin_CHECK);
}
int BoardA19::resolution() {
  int bit_a = int(!digitalRead(pin_RES_A));
  int bit_b = int(!digitalRead(pin_RES_B));
  int bit_c = int(!digitalRead(pin_RES_C));

  int exp = 1 * bit_a + 2 * bit_b + 4 * bit_c;

  return exp;
}