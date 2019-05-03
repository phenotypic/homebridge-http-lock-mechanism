# homebridge-http-lock-mechanism

[![npm](https://img.shields.io/npm/dt/homebridge-http-lock-mechanism.svg)](https://www.npmjs.com/package/homebridge-http-lock-mechanism) [![npm](https://img.shields.io/npm/v/homebridge-http-lock-mechanism.svg)](https://www.npmjs.com/package/homebridge-http-lock-mechanism)

## Description

This [homebridge](https://github.com/nfarina/homebridge) plugin exposes a web-based locking device to to Apple's [HomeKit](http://www.apple.com/ios/home/). Using simple HTTP requests, you can turn lock/unlock the device.

## Installation

1. Install [homebridge](https://github.com/nfarina/homebridge#installation-details)
2. Install this plugin: `sudo npm install -g homebridge-http-lock-mechanism`
3. Update your `config.json` file (See below).

## Configuration

```json
"accessories": [
     {
       "accessory": "HTTPLock",
       "name": "Lock",
       "openURL": "http://myurl.com/open",
       "closeURL": "http://myurl.com/close"
     }
]
```

### Core
| Key | Description | Default |
| --- | --- | --- |
| `accessory` | Must be `HTTPLock` | N/A |
| `name` | Name to appear in the Home app | N/A |
| `openURL` | URL to trigger unlock | N/A |
| `closeURL` | URL to trigger lock | N/A |

### Optional fields
| Key | Description | Default |
| --- | --- | --- |
| `autoLock` _(optional)_ | Whether your lock should re-lock after being opened | `false` |
| `autoLockDelay` _(optional)_ | Time (in seconds) until your lock will auto lock if enabled | `10` |

### Additional options
| Key | Description | Default |
| --- | --- | --- |
| `timeout` _(optional)_ | Time (in milliseconds) until the accessory will be marked as "Not Responding" if it is unreachable | `3000` |
| `http_method` _(optional)_ | The HTTP method used to communicate with the lock | `GET` |
| `username` _(optional)_ | Username if HTTP authentication is enabled | N/A |
| `password` _(optional)_ | Password if HTTP authentication is enabled | N/A |
| `model` _(optional)_ | Appears under the "Model" field for the device | `homebridge-http-lock-mechanism` |
| `serial` _(optional)_ | Appears under the "Serial" field for the device | N/A |
| `manufacturer` _(optional)_ | Appears under the "Manufacturer" field for the device | `Tom Rodrigues` |
