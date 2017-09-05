# esp8266-nonos-adc-thingspeak
This is a sample ESP8266 application to monitor temperature, humidity, air pressure and battery voltage. All readings are send to thingspeak.com.
## Hardware
Air parameters are measured with BME280 sensor connected to the [Wemos D1 mini](https://www.wemos.cc/product/d1-mini.html).

* Note that additional resistor has to be added to voltage divider on ADC pin if you want to measure higher voltage than 3V3.
* ESP8266 goes to sleep betwen measurements, but to be able to wake up itself D0 and RST pins has to be shortened (XPD_DCDC to EXT_RSTB). 

## Build
To build this you have to set up [esp-open-sdk](https://github.com/pfalcon/esp-open-sdk) using default settings. Then `make` and `make flash` if you are using macOS. For other systems you need to modify paths in Makefile.