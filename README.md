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
| Key | Description | Type | Default |
| --- | --- | --- | --- |
| `accessory` | Must be `HTTPLock` | `string` | N/A |
| `name` | Name to appear in the Home app | `string` | N/A |
| `openURL` | URL to trigger unlock | `string` | N/A |
| `closeURL` | URL to trigger lock | `string` | N/A |

### Optional fields
| Key | Description | Type | Default |
| --- | --- | --- | --- |
| `autoLock` _(optional)_ | Whether your lock should re-lock after being opened (default `false`) | `boolean` | `false` |
| `autoLockDelay` _(optional)_ | Time (in seconds) until your lock will auto lock if enabled (default is `10`) | `integer` (seconds) | `5` |

### Additional options
| Key | Description | Type | Default |
| --- | --- | --- | --- |
| `timeout` _(optional)_ | Time until the accessory will be marked as "Not Responding" if it is unreachable | `integer` (milliseconds) | `5000` |
| `http_method` _(optional)_ | The HTTP method used to communicate with the lock | `string` | `GET` |
| `username` _(optional)_ | Username if HTTP authentication is enabled | `string` | N/A |
| `password` _(optional)_ | Password if HTTP authentication is enabled | `string` | N/A |
| `model` _(optional)_ | Appears under "Model" for your accessory in the Home app | `string` | `homebridge-http-lock-mechanism` |
| `serial` _(optional)_ | Appears under "Serial" for your accessory in the Home app | `string` | `HTTP Serial Number` |
| `manufacturer` _(optional)_ | Appears under "Manufacturer" for your accessory in the Home app | `string` | `HTTP Manufacturer` |
