An embedded color recognition system built using the Arduino ecosystem. The device utilizes a custom-built sensor composed of an RGB LED and a Photoresistor (LDR) to identify the color of physical objects based on reflected light intensity.

Without any changes it can easily identify up to 4 different colours (red, green, blue and yellow). However, this can be adjusted to any number. 

You only need to change the size of _sampleColors_ table to desired number and change the message written on the LCD screen.

Hardware used:
1. Microcontroller: Arduino Uno / Nano compatible.
2. Display: 16x2 LCD with I2C Backpack
3. RGB LED (Common Cathode) and 3 330Ω resistors.
4. Photoresistor (LDR) with a 4.7kΩ pull-down resistor (Voltage Divider)
5. Custom light-isolated housing (LED and photoresistor need to be inside of the housing like in the _presentation.jpg_)

![Schematic](https://github.com/IgorTyrajski/Arduino_color_detection/blob/main/Schematic.png)
![Presentation](https://github.com/IgorTyrajski/Arduino_color_detection/blob/main/Presentation.jpg)
