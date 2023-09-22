#include "IF.h"

BoardA5::BoardA5() {
}
void BoardA5::init() {
  pinMode(pin_FD, INPUT);
  pinMode(pin_N_LPD, INPUT);
  pinMode(pin_N_HPD, INPUT);
}
bool BoardA5::in_band() {
  return digitalRead(pin_FD);
}
bool BoardA5::is_low_level() {
  return !digitalRead(pin_N_LPD);
}
bool BoardA5::is_high_level() {
  return !digitalRead(pin_N_HPD);
}