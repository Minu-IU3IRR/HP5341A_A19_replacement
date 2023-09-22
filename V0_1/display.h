#include <Arduino.h>

class BoardA15 {
private:

  int pin_Addr = 23;
  int pin_STAR = 22;
  int pin_OVEN = 25;
  int pin_REMOTE = 28;
  int pin_KILO = 33;
  int pin_MEGA = 35;
  int pin_GIGA = 37;
  int pin_GATE = 42;
  int pin_RELEASE = 31;
  int pin_GRAB = 24;
  int pin_CU = 27;
  int pin_CD = 26;
  int pin_LATCH_DP = 29;
  int pin_ADD = 40;
  int pin_RESET = 30;
  int pin_A = 32;
  int pin_B = 34;
  int pin_C = 38;
  int pin_D = 36;
  int bds_pins[4] = { pin_A, pin_B, pin_C, pin_D };

  int DISPLAY_DIGITS = 10;

  void ram_write_enable(bool state);
  void counter_increment();
  void counter_state(bool en);

public:

  BoardA15();
  void init();
  void reset();
  void light_addr(bool state);
  void light_kilo();
  void light_mega();
  void light_giga();
  void light_gate_pulse();
  void light_oven(bool state);
  void light_star_pulse();
  void light_rmt(bool state);
  void print(uint64_t number);
  void decimal_position(int position);
};