String status_string() {

  String output = "";


  output += "FD: ";
  output += IF.in_band() ? "1 | " : "0 | ";
  output += "LPD: ";
  output += IF.is_low_level() ? "1 | " : "0 | ";
  output += "HPD: ";
  output += IF.is_high_level() ? "1 " : "0 ";

  output += "   band: ";
  output += String(filter.band);
  output += "   mode: ";
  output += front_panel.input_high_range() ? "1 " : "0 ";
  output += "   check: ";
  output += front_panel.input_check() ? "1 " : "0 ";

  output += "   ";
  output +="valid_high_band_signal = ";
  output += valid_high_band_signal ? "1 " : "0 ";
  output += "   resolution : ";
  output += String(front_panel.resolution());
  

  return output;
}