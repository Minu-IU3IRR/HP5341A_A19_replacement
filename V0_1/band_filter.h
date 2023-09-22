#include <Arduino.h>

class BoardA10 {
private:

  int pin_N_BAND_INC = A4;   //(BAND 0) line
  int pin_N_BAND_ZERO = A5;  // (BAND+1) line

  void increment();
  void reset();

public:

  int band = 0;
  BoardA10();
  void init();
  void set(int filter_index);
};