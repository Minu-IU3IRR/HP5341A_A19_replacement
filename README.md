# HP5341A_A19_replacement

A project for restoring old HP5341A frequency counters

whis repo contains the Arduino sketch that enables full control over the intrument even via Serial port usign standard VISA commands, if wou use the Arduno mega you will find the kicad project for the shield that allows easy connection of the wires on the mainboard and socket for the original display (to maintain the fashon factor of course:).
if you with to use another board make shure that 5v can be handeled, all the logic on the instrument is 5V.

-VERY IMPORTANT!
if you supply power to the arduino with the shield make shure to disconnect the 5V positive wire from the USB port so you will not connect your computer's 5V bus to the insturment one, BAD things can occur. the ground wire must remain connected. to supply the arduino from your PC just avoid soldering the +5V pins on the shield and the voltages are separated, keep in mind that the instrument must supply the display if original, it can pull up to 1A that the arduno or PC can not provide.


Feel free to reproduce all the content, just make shure to link this repo as the source!

under any circumstance i will take ANY responsability for damage of any kind to anything or anyone from reproducing any part of the cntents of this repo.....
