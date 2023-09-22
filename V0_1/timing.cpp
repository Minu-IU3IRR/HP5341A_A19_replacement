#include "timing.h"


BoardA17::BoardA17() {
}
void BoardA17::init() {
  pinMode(pin_N_ARM, OUTPUT);
  pinMode(pin_N_GATE, INPUT);

  digitalWrite(pin_N_ARM, HIGH);

  pinMode(pin_N_START_SR, OUTPUT);
  pinMode(pin_N_SR_DONE, INPUT);

  digitalWrite(pin_N_START_SR, HIGH);
}
void BoardA17::arm() {
  //arm the timebase board, reset shift counters and start gate tmer
  digitalWrite(pin_N_ARM, LOW);
  delayMicroseconds(10);
  digitalWrite(pin_N_ARM, HIGH);
  delayMicroseconds(10);  // wait for system ready
}
bool BoardA17::gate_state() {
  //get gate status
  return !bool(digitalRead(pin_N_GATE));
}
void BoardA17::start_deadtime() {
  digitalWrite(pin_N_START_SR, LOW);
  delayMicroseconds(10);
  digitalWrite(pin_N_START_SR, HIGH);
}
bool BoardA17::deadtime_expired() {
  return !bool(digitalRead(pin_N_SR_DONE));
}