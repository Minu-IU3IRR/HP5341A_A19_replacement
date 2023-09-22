#include <Arduino.h>

class VISA {
private:
  unsigned long baud;
public:
  VISA(unsigned long baud_rate);
  void open();
  bool parse_scpi(String input, String& command);
  bool parse_visa(String visaCommand, String& command, String& arguments);
  void write(String response);
  void error(int errorCode, String errorMessage);
};