<p align="center">
  <a href="https://github.com/homebridge/homebridge"><img src="https://raw.githubusercontent.com/homebridge/branding/master/logos/homebridge-color-round-stylized.png" height="140"></a>
</p>

<span align="center">

# homebridge-http-lock-mechanism

[![npm](https://img.shields.io/npm/v/homebridge-http-lock-mechanism.svg)](https://www.npmjs.com/package/homebridge-http-lock-mechanism) [![npm](https://img.shields.io/npm/dt/homebridge-http-lock-mechanism.svg)](https://www.npmjs.com/package/homebridge-http-lock-mechanism)

</span>

## Description

This [homebridge](https://github.com/nfarina/homebridge) plugin exposes a web-based locking device to Apple's [HomeKit](http://www.apple.com/ios/home/). Using simple HTTP requests, the plugin allows you to lock/unlock the device. **Please look at [homebridge-web-lock](https://github.com/Tommrodrigues/homebridge-web-lock) if you want a plugin that allows for real-time status updates.**

Find script samples for the lock in the _examples_ folder.

## Installation

1. Install [homebridge](https://github.com/nfarina/homebridge#installation-details)
2. Install this plugin: `npm install -g homebridge-http-lock-mechanism`
3. Update your `config.json` file

## Configuration

```json
"accessories": [
     {
       "accessory": "HTTPLock",
       "name": "Lock",
       "apiroute": "http://myurl.com"
     }
]
```

### Core
| Key | Description | Default |
| --- | --- | --- |
| `accessory` | Must be `HTTPLock` | N/A |
| `name` | Name to appear in the Home app | N/A |
| `apiroute` | Root URL of your device | N/A |

### Optional fields
| Key | Description | Default |
| --- | --- | --- |
| `autoLock` _(optional)_ | Whether your lock should re-lock after being opened | `false` |
| `autoLockDelay` _(optional)_ | Time (in seconds) until your lock will auto lock if enabled | `10` |
| `polling` | Whether the state should be polled at intervals | `false` |
| `pollInterval` | Time (in seconds) between device polls (if `polling` is enabled) | `120` |
| `statusURL` | URL to retrieve state on poll (should return `0` or `1`) | N/A |

### Additional options
| Key | Description | Default |
| --- | --- | --- |
| `timeout` _(optional)_ | Time (in milliseconds) until the accessory will be marked as _Not Responding_ if it is unreachable | `3000` |
| `http_method` _(optional)_ | HTTP method used to communicate with the device | `GET` |
| `username` _(optional)_ | Username if HTTP authentication is enabled | N/A |
| `password` _(optional)_ | Password if HTTP authentication is enabled | N/A |
| `model` _(optional)_ | Appears under the _Model_ field for the accessory | plugin |
| `serial` _(optional)_ | Appears under the _Serial_ field for the accessory | version |
| `manufacturer` _(optional)_ | Appears under the _Manufacturer_ field for the accessory | author |
| `firmware` _(optional)_ | Appears under the _Firmware_ field for the accessory | version |

## API Interfacing

Your API should be able to:

1. Return JSON information when it receives `/status`:
```
{
    "currentState": INT_VALUE
}
```

2. Set the state when it receives:
```
/setState?value=INT_VALUE
```

## State key
| State | Description |
| --- | --- |
| `0` | Open |
| `1` | Closed |
