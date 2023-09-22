#include <Arduino.h>

class BoardA18 {
private:
  int pin_N_SELECT = A11;
  int pin_SHIFT = A2;

  int pin_DIGIT_A = A7;
  int pin_DIGIT_B = A8;
  int pin_DIGIT_C = A9;
  int pin_DIGIT_D = A10;
  void shift();
  int read_bcd();
public:
  BoardA18();
  void init();
  uint64_t read();
};