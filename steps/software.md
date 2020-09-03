# Software Setup #
The software part of this project includes the arduino code, and how to get the arduino code onto the device. [wduraes tutorial](https://github.com/wduraes/Workshops/tree/master/IoT%20101%20for%20Makers) does a great explanation on how to setup Arduino to work with the ESP8266 board inlcuding necessary libraries for mqtt.

## Arduino Setup ##
Add additional board definition files
Under Files/Preferences copy this string into the Additional Board Manager URLs field. (Note you can have multiple by seperating them with a ,)
### For ESP8266 ###
`http://arduino.esp8266.com/stable/package_esp8266com_index.json`
### For ESP32 ###
`https://dl.espressif.com/dl/package_esp32_index.json`

Restart Arduino to update the boards.
Add necessary libraries.
Under Tools/Library Manager, use the search bar and add the following libraries
- Adafruit MQTT by Adafruit

You will also have to manually add the [Tone32 library from Ibernstone](https://github.com/lbernstone/Tone32) if you are using the ESP32. Copy the repo into your Arduino/Libraries folder.

## Adafruit.io Setup ##
Get yourself an account, its free.
Create a feed. Note your username and AIO key.

## Code Changes ##
There are commented #include statements depending on if you are using the ESP8266 or ESP32
You need to add your SSID, wifi password, Adafruit.io user name, adafruit.io key and the name of your feed.
