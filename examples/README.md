## Description

This script interfaces with [homebridge](https://github.com/nfarina/homebridge) to expose a relay to Apple's [HomeKit](http://www.apple.com/ios/home/), allowing you to integrate a lock into your smart home.

## Requirements

* NodeMCU

* Relay Module

* Pin header cables

* Micro-USB cable

## How-to

1. First, install the `ArduinoJson` library from the _Library manager_ in the Arduino IDE, then follow [this](https://gist.github.com/Tommrodrigues/8d9d3b886936ccea9c21f495755640dd) gist which walks you through how to flash a NodeMCU using the Arduino IDE. The `.ino` file referred to is the `NodeMCU-Lock.ino` file included in this repository. When doing this, you should change the username and password, and insert your own SSL certificates.

2. Assuming that you already have [homebridge](https://github.com/nfarina/homebridge#installation) set up, the next thing you will have to do is install the plugin:
```
npm install -g homebridge-http-lock-mechanism
```

3. Finally, update your `config.json` file following the example below:

```json
"accessories": [
    {
       "accessory": "HTTPLock",
       "name": "Garage",
       "apiroute": "https://lock.local",
       "username": "admin",
       "password": "esp8266"
     }
]
```

## Wiring

![Diagram](https://i.ibb.co/Jrzr2Hm/68747470733a2f2f696d6167652e6962622e636f2f68454468464c2f576972696e672d52656c61792d4469616772616d2e6a7067.jpg)
