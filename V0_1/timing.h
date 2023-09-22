#include <Arduino.h>

class BoardA17 {
private:

  int pin_N_ARM = A6;
  int pin_N_GATE = 13;
  int pin_N_START_SR = A1;
  int pin_N_SR_DONE = 12;

public:
  BoardA17();
  void init();
  void arm();
  bool gate_state();
  void start_deadtime();
  bool deadtime_expired();
};