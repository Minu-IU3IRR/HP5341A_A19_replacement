
#include "VISA.h"

VISA::VISA(unsigned long baud_rate){
  baud = baud_rate;
}

void VISA::open(){
  Serial.begin(baud);
}

bool VISA::parse_scpi(String input, String& command){
  if(input.length() > 0){
    if(input.charAt(0) == '*'){
      command = input;
      return true;
    }
  }
  return false;
}

bool VISA::parse_visa(String visaCommand, String& command, String& arguments) {
  /*parse the VisaCommand to command and  arguments variable, COMMAND:...(arguments), returns true if arguments are commands or false if is value*/

  // Find the position of the ':' character
  int colonPos = visaCommand.indexOf(':');

  if (colonPos != -1) {
    // Extract the command and arguments if the ':' is not the last character
    if (colonPos < visaCommand.length() - 1) {
      command = visaCommand.substring(0, colonPos);
      arguments = visaCommand.substring(colonPos + 1);
      return true;  // Argument is present
    } else {
      // No argument, treat the entire string as the command
      command = visaCommand;
      arguments = "";
      return false;  // No argument
    }
  } else {
    // If ':' is not found, treat the entire string as the command
    command = visaCommand;
    arguments = "";
    return false;  // No argument
  }
}

void VISA::write(String response) {
  Serial.println(response);
}

void VISA::error(int errorCode, String errorMessage) {
  write("ERR:" + String(errorCode) + "," + errorMessage);
}
