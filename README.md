# esp8266-nonos-adc-thingspeak
This is a sample ESP8266 application to monitor soil moisture and send readings to thingspeak.com.
## Hardware
Moisture is measured with this kind of sensor

![sensor](http://obrazki.elektroda.pl/4588601200_1491160818.jpg)

connected to the [Wemos D1 mini](https://www.wemos.cc/product/d1-mini.html).

* Note that D1 mini has a voltage divider on its ADC pin, so sensor can be directly connected to the board.
* ESP8266 goes to sleep betwen measurements, but to be able to wake up itself D0 and RST pins has to be shortened (XPD_DCDC to EXT_RSTB). 

## Build
To build this you have to set up [esp-open-sdk](https://github.com/pfalcon/esp-open-sdk) using default settings. Then `make` and `make flash` if you are using Mac OS X. For other systems you need to modify paths in Makefile.