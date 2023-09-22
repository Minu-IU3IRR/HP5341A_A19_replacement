#include <Arduino.h>

class BoardA19 {
private:
  int pin_MANUAL = 6;
  int pin_N_BAND_SELECT = A0;
  int pin_EIGHTY = 3;  // front panel selection, auto signal souting in hardware
  int pin_CHECK = 8;   // self test position
  int pin_RES_A = 4;
  int pin_RES_B = 5;
  int pin_RES_C = 7;

public:
  BoardA19();
  void init();
  bool band_automatic();
  bool band_button_pressed();
  bool input_high_range();
  bool input_check();
  int resolution();
};