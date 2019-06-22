# lora

## Sparkfun LoRa RF Pro

- This work is done on MacOS.
- Following the Sparkfun [hookup instructions](https://learn.sparkfun.com/tutorials/sparkfun-samd21-pro-rf-hookup-guide?_ga=2.83163295.82973091.1561161722-1234373862.1561161722).
- When installing the Arduino SAMD21 board definition package, _get a version from the 1.6 line_. At the moment, the 1.8 versions do not work correctly with the Sparkfun board definition. The symptom is that the upload fails with a Java error, if you use a 1.8 version. Presumably Arduino or Sparkfun will fix the problem sometime.
- You can run multiple copies of Arduino.app by navigating into the bundle macos/ folder and running `./Arduino`.
- `Arduino.app` defaults to placing artifacts in ~/Documents/Arduino.
- Install the RadioHead uncompressed zip file  ~/Documents/Arduino/libraries.
- Use the Sparkfun examples for the LoRa RF Pro. The RadioHead examples are (mostly) not relevant for this board.
- The print device on the Sparkfun board is referenced as `printUSB`, instead of `print`.
