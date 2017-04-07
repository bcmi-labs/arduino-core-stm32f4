## 1.0.1 - 2017-04-07
###### Core:
  - Fixed USB CDC issue if the chunk is greater than 64 bytes
  - Fixed I2C Pin definition
  - Fixed CAN-BUS pin definition
  - Added CAN-BUS port 2 definition
  - Fixed ESP8266 Upload issue
    - The sleep time before the stm32 sketch upload should be set to 3 seconds and a patched version of 0.4.9 Espressif tool is needed.
    - Is possible to use the standard 0.4.9 tool using 230400bps upload speed.
  - Fixed IRQ vector Table for DSI and QUAD SPI

###### library
- Audio:
  - added amp()
  - Updated README.adoc

###### Miscellany:
  - Added ChangeLog.txt
  - Code Cleanup

## 1.0.0 - 2017-03-14
First release
