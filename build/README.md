This part of the project is peding to be update.

`idf.py` is the official build tool provided by Espressif. It is a Python-based, cross-platform command-line tool that integrates all capabilities required for ESP32 and ESP8266 development. It is designed to be multi-platform and supports Windows, macOS, and Linux platforms.

You can use `idf.py` to build and flash the code to the ESP32 or ESP8266. You can find more information about `idf.py` in the official documentation: [https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html)

### ESP32

To flash the code to the ESP32, you need to follow the next steps:

1. Download and install the [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html#installation-step-by-step) toolchain.
2. Download the code
3. Open the code in the Arduino IDE
4. Upload the code to the ESP32
5. Connect the ESP32 to your computer
6. Open the terminal and go to the project folder
7. Run `idf.py menuconfig` to configure the project
8. Run `idf.py build` to build the project
9. Run `idf.py -p PORT flash` to flash the project to the ESP32

### ESP8266

To flash the code to the ESP8266, you need to follow the next steps:

1. Download and install the [ESP8266 toolchain](https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/get-started/index.html#setup-toolchain).
2. Download the code
3. Open the code in the Arduino IDE
4. Upload the code to the ESP8266
5. Connect the ESP8266 to your computer
6. Open the terminal and go to the project folder
7. Run `idf.py menuconfig` to configure the project
8. Run `idf.py build` to build the project
9. Run `idf.py -p PORT flash` to flash the project to the ESP8266
