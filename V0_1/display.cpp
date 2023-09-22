#include "display.h"

BoardA15::BoardA15() {
}

void BoardA15::init() {
  pinMode(pin_Addr, OUTPUT);
  pinMode(pin_STAR, OUTPUT);
  pinMode(pin_OVEN, OUTPUT);
  pinMode(pin_REMOTE, OUTPUT);
  pinMode(pin_KILO, OUTPUT);
  pinMode(pin_MEGA, OUTPUT);
  pinMode(pin_GIGA, OUTPUT);
  pinMode(pin_GATE, OUTPUT);
  pinMode(pin_RELEASE, OUTPUT);
  pinMode(pin_GRAB, OUTPUT);
  pinMode(pin_CU, OUTPUT);
  pinMode(pin_CD, OUTPUT);
  pinMode(pin_LATCH_DP, OUTPUT);
  pinMode(pin_ADD, OUTPUT);
  pinMode(pin_RELEASE, OUTPUT);
  pinMode(pin_RESET, OUTPUT);
  pinMode(pin_A, OUTPUT);
  pinMode(pin_B, OUTPUT);
  pinMode(pin_C, OUTPUT);
  pinMode(pin_D, OUTPUT);

  digitalWrite(pin_STAR, HIGH);
  digitalWrite(pin_GATE, HIGH);

  //multiplexer init
  counter_state(true);

  digitalWrite(pin_CU, HIGH);
  digitalWrite(pin_CD, HIGH);
  digitalWrite(pin_LATCH_DP, HIGH);
  digitalWrite(pin_RELEASE, HIGH);
  digitalWrite(pin_RESET, HIGH);
  digitalWrite(pin_A, HIGH);
  digitalWrite(pin_B, HIGH);
  digitalWrite(pin_C, HIGH);
  digitalWrite(pin_D, HIGH);

  light_addr(false);
  light_oven(false);
  light_rmt(false);
  light_kilo();

  // ram write disable
  ram_write_enable(false);
}

void BoardA15::light_addr(bool state) {
  digitalWrite(pin_Addr, state);
}

void BoardA15::light_kilo() {
  digitalWrite(pin_KILO, LOW);
  digitalWrite(pin_MEGA, HIGH);
  digitalWrite(pin_GIGA, HIGH);
}
void BoardA15::light_mega() {
  digitalWrite(pin_KILO, HIGH);
  digitalWrite(pin_MEGA, LOW);
  digitalWrite(pin_GIGA, HIGH);
}
void BoardA15::light_giga() {
  digitalWrite(pin_KILO, HIGH);
  digitalWrite(pin_MEGA, HIGH);
  digitalWrite(pin_GIGA, LOW);
}
void BoardA15::light_gate_pulse() {
  digitalWrite(pin_GATE, LOW);
  delayMicroseconds(3);
  digitalWrite(pin_GATE, HIGH);
}
void BoardA15::light_oven(bool state) {
  digitalWrite(pin_OVEN, state);
}
void BoardA15::light_star_pulse() {
  digitalWrite(pin_STAR, LOW);
  delayMicroseconds(3);
  digitalWrite(pin_STAR, HIGH);
}
void BoardA15::light_rmt(bool state) {
  digitalWrite(pin_REMOTE, !state);
}
void BoardA15::reset() {
  digitalWrite(pin_RESET, LOW);
  delayMicroseconds(10);
  digitalWrite(pin_RESET, HIGH);

  print(0);
  decimal_position(0);
  light_oven(false);
  light_rmt(false);
}
void BoardA15::print(uint64_t number) {
  //stop counter and reset addr
  counter_state(false);
  ram_write_enable(true);

  //println64(&Serial, number);

  for (int i = 0; i < DISPLAY_DIGITS; i++) {
    // Extract the last digit
    uint8_t digit = number % 10;

    // Convert the decimal digit to BCD
    uint8_t bcd = (digit / 10) << 4 | (digit % 10);

    //--------------------------------------------------------------
    // if residual number == 0 -> remove leading zeros pointing to BCD 15
    if (number == 0 && i > 0) {
      bcd = 15;
    }

    // Remove the last digit from the number
    number /= 10;

    // Invert all bits of the BCD value
    bcd = ~bcd;

    // Send the BCD value to the pins
    for (int j = 0; j < 4; j++) {
      // Set the BCD pins based on the bits of bcd
      digitalWrite(bds_pins[j], (bcd >> j) & 1);
    }

    // Pulse the count_up only if not last digit
    if (i != (DISPLAY_DIGITS - 1)) {
      counter_increment();
    }
    delayMicroseconds(10);  // Adjust this delay as needed
  }


  ram_write_enable(false);
  counter_state(true);
}

void BoardA15::decimal_position(int position) {
  counter_state(false);
  for (int i = 0; i < DISPLAY_DIGITS; i++) {
    if (i == position) {
      digitalWrite(pin_LATCH_DP, LOW);
      delayMicroseconds(10);
      digitalWrite(pin_LATCH_DP, HIGH);
      break;
    }
    counter_increment();
  }
  counter_state(true);
}

//********************************************private

void BoardA15::ram_write_enable(bool state) {
  digitalWrite(pin_ADD, !state);
  delayMicroseconds(10);
}
void BoardA15::counter_increment() {
  digitalWrite(pin_CU, LOW);
  delayMicroseconds(10);  // Adjust this delay as needed
  digitalWrite(pin_CU, HIGH);
}

void BoardA15::counter_state(bool en) {
  int a_pin = pin_RELEASE;  // release oscillator
  int b_pin = pin_GRAB;     //latch gate to grab zero in memory
  if (en) {
    a_pin = pin_GRAB;
    b_pin = pin_RELEASE;
  }
  digitalWrite(a_pin, HIGH);
  digitalWrite(b_pin, LOW);
  delayMicroseconds(10);
  digitalWrite(b_pin, HIGH);
}
