# homebridge-http-lock-mechanism

#### Homebridge plugin to control a web-based lock

## Description

homebridge-http-lock-mechanism exposes a lock to HomeKit, and makes it controllable via simple HTTP requests.

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
| Key | Description |
| --- | --- |
| `accessory` | Must be `HTTPLock` |
| `name` | Name to appear in the Home app |
| `openURL` | URL to trigger unlock |
| `closeURL` | URL to trigger lock |

### Optional fields
| Key | Description |
| --- | --- |
| `autoLock` _(optional)_ | Whether your lock should re-lock after being opened (default `false`) |
| `autoLockDelay` _(optional)_ | Time (in seconds) until your lock will auto lock if enabled (default is `10`) |

### Additional options
| Key | Description |
| --- | --- |
| `timeout` _(optional)_ | Time (in milliseconds) until your lock will be marked as "Not Responding" if it is unreachable (`5000` is default) |
| `http_method` _(optional)_ | The HTTP method used to communicate with the lock (`GET` is default) |
| `username` _(optional)_ | Username if HTTP authentication is enabled |
| `password` _(optional)_ | Password if HTTP authentication is enabled |
| `model` _(optional)_ | Appears under "Model" for your lock in the Home app |
| `serial` _(optional)_ | Appears under "Serial" for your lock in the Home app |
| `manufacturer` _(optional)_ | Appears under "Manufacturer" for your lock in the Home app |
