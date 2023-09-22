#include "IF.h"
#include "band_filter.h"
#include "display.h"
#include "counter.h"
#include "front_panel.h"
#include "timing.h"
#include "VISA.h"

#define IDN "HP,5341A,ArduinoVisa,FW0.1"
unsigned long baud_rate = 115200;

VISA interface = VISA(baud_rate);

BoardA5 IF = BoardA5();
BoardA10 filter = BoardA10();
BoardA15 display = BoardA15();
BoardA17 timing = BoardA17();
BoardA18 counter = BoardA18();
BoardA19 front_panel = BoardA19();


bool update = false;  // becomes true if ay parameter has changed = reset
bool waiting_deadtime = false;
bool valid_high_band_signal = false;

int resolution = 0;
bool high_range = 0;
bool band_auto = false;

uint64_t last_reading = 0;


#define BAND_COUNT 9
uint64_t band_offset[7][10] = {
  { 0, 500000000, 750000000, 1000000000, 1500000000, 2000000000, 2500000000, 3000000000, 3500000000, 4000000000 },
  { 0, 50000000, 75000000, 100000000, 150000000, 200000000, 250000000, 300000000, 350000000, 400000000 },
  { 0, 5000000, 7500000, 10000000, 15000000, 20000000, 25000000, 30000000, 35000000, 40000000 },
  { 0, 500000, 750000, 1000000, 1500000, 2000000, 2500000, 3000000, 3500000, 4000000 },
  { 0, 50000, 75000, 100000, 150000, 200000, 250000, 300000, 350000, 400000 },
  { 0, 5000, 7500, 10000, 15000, 20000, 25000, 30000, 35000, 40000 },
  { 0, 500, 750, 1000, 1500, 2000, 2500, 3000, 3500, 4000 },
};


void setup() {

  interface.open();

  IF.init();
  filter.init();
  display.init();
  counter.init();
  front_panel.init();
  timing.init();

  update = true;
}

void loop() {

  //---------------------------------------------------------------remote control
  if (Serial.available() > 0) {
    String serial_input = Serial.readStringUntil('\n');
    serial_input.trim();  // remove \n at end of string

    String command;
    String argument;

    bool is_scpi = interface.parse_scpi(serial_input, command);
    if (is_scpi) {
      if (command == "*IDN?") {
        interface.write(IDN);
      } else {
        interface.error(1, "invalid VISA command");
      }
    }
    bool is_visa = interface.parse_visa(serial_input, command, argument);
    if (is_visa) {
      //valid command
      if (argument == "FREQ?") {
        String frequeuncy_sring = uint64ToString(last_reading);
        for (int i = 0; i < resolution; i++) {
          frequeuncy_sring += "0";
        }
        interface.write(frequeuncy_sring);
      } else if (argument == "BAND?") {
        interface.write(String(filter.band));
      } else if (argument == "RES?") {
        interface.write(String(resolution));
      } else if (argument == "DEAD?") {
        interface.write(String(int(waiting_deadtime)));
      } else if (argument == "GATE?") {
        interface.write(String(int(!waiting_deadtime)));
      } else if (argument == "STAT?") {
        interface.write(status_string());
      } else {
        interface.error(2, "invalid VISA command");
      }
    }
  }

  //---------------------------------------------------------------update enviroment

  check_change(front_panel.resolution(), &resolution, &update);
  check_change(front_panel.input_high_range(), &high_range, &update);
  check_change(front_panel.band_automatic(), &band_auto, &update);

  //---------------------------------------------------------------range management
  if (high_range) {
    if (IF.is_low_level()) {  // display
      display.light_star_pulse();
    }

    if (band_auto) {
      valid_high_band_signal = IF.in_band() && IF.is_high_level();
      if (!valid_high_band_signal) {
        for (int band = 0; band <= BAND_COUNT; band++) {
          filter.set(band);
          delay(1);
          if (IF.in_band() && !IF.is_low_level()) {
            update = true;
            break;
          }
        }
      }
    } else {
      valid_high_band_signal = IF.in_band();
      if (front_panel.band_button_pressed()) {
        delay(300);  //debounce

        int new_band = filter.band + 1;
        if (new_band > BAND_COUNT) {  // rollover
          new_band = 0;
        }
        //Serial.println("manual band selection : " + String(current_band));
        filter.set(new_band);
        update = true;
      }
    }
  } else if (front_panel.input_check()) {
    filter.set(1);  // set fixed band
  } else {
    //band eighty
  }

  //--------------------------------------------------------------- update
  if (update) {
    update = false;
    waiting_deadtime = false;
    last_reading = 0;

    display.reset();
    timing.arm();

    // display_update
    if (resolution < 3) {
      display.light_kilo();
    } else if (resolution < 6) {
      display.light_mega();
    } else {
      display.light_giga();
    }

    int decimal_position = 3 - (resolution % 3 == 0);
    display.decimal_position(decimal_position);
  }

  // ------------------------------------------------------------- gating
  if (timing.gate_state()) {
    display.light_gate_pulse();
  } else {
    if (!waiting_deadtime) {
      timing.start_deadtime();
      waiting_deadtime = true;

      uint64_t reading = counter.read();

      if (high_range) {

        //println64(&Serial, reading);
        //println64(&Serial, band_offset[resolution][current_band]);
        if (valid_high_band_signal) {
          if (!front_panel.input_check()) {
            reading = reading + band_offset[resolution][filter.band];
          }
        } else {
          reading = 0;
        }
      }
      display.print(reading);
      last_reading = reading;
      //println64(&Serial, reading);
    }
  }
  if (waiting_deadtime) {
    if (timing.deadtime_expired()) {
      waiting_deadtime = false;
      timing.arm();
    }
  }
}

template<typename T>
void check_change(T current_value, T* old_value, bool* change_detected) {
  if (current_value != *old_value) {
    *old_value = current_value;
    *change_detected = true;
  }
}

String uint64ToString(uint64_t input) {
  String result = "";
  uint8_t base = 10;

  do {
    char c = input % base;
    input /= base;

    if (c < 10)
      c +='0';
    else
      c += 'A' - 10;
    result = c + result;
  } while (input);
  return result;
}