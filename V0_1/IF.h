#include <Arduino.h>

class BoardA5 {
private:
  int pin_FD = 2;
  int pin_N_LPD = 10;
  int pin_N_HPD = 11;
public:
  BoardA5();
  void init();
  bool in_band();
  bool is_low_level();
  bool is_high_level();
};