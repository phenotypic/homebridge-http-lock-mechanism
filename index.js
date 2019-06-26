var Service, Characteristic
const request = require('request')
const packageJson = require('./package.json')

module.exports = function (homebridge) {
  Service = homebridge.hap.Service
  Characteristic = homebridge.hap.Characteristic
  homebridge.registerAccessory('homebridge-http-lock-mechanism', 'HTTPLock', HTTPLock)
}

function HTTPLock (log, config) {
  this.log = log

  this.name = config.name

  this.manufacturer = config.manufacturer || packageJson.author.name
  this.serial = config.serial || packageJson.version
  this.model = config.model || packageJson.name
  this.firmware = config.firmware || packageJson.version

  this.username = config.username || null
  this.password = config.password || null
  this.timeout = config.timeout || 3000
  this.http_method = config.http_method || 'GET'

  this.openURL = config.openURL
  this.closeURL = config.closeURL

  this.autoLock = config.autoLock || false
  this.autoLockDelay = config.autoLockDelay || 10

  if (this.username != null && this.password != null) {
    this.auth = {
      user: this.username,
      pass: this.password
    }
  }

  this.service = new Service.LockMechanism(this.name)
}

HTTPLock.prototype = {

  identify: function (callback) {
    this.log('Identify requested!')
    callback()
  },

  _httpRequest: function (url, body, method, callback) {
    request({
      url: url,
      body: body,
      method: this.http_method,
      timeout: this.timeout,
      rejectUnauthorized: false,
      auth: this.auth
    },
    function (error, response, body) {
      callback(error, response, body)
    })
  },

  setLockTargetState: function (value, callback) {
    var url
    this.log('Setting LockTargetState to %s', value)
    if (value === 1) {
      url = this.closeURL
    } else {
      url = this.openURL
    }
    this._httpRequest(url, '', this.http_method, function (error, response, responseBody) {
      if (error) {
        this.log.warn('Error setting LockTargetState: %s', error.message)
        callback(error)
      } else {
        if (value === 1) {
          this.service.setCharacteristic(Characteristic.LockCurrentState, Characteristic.LockCurrentState.SECURED)
          this.log('Closed the lock')
        } else {
          this.log('Opened the lock')
          this.service.setCharacteristic(Characteristic.LockCurrentState, Characteristic.LockCurrentState.UNSECURED)
          if (this.autoLock) {
            this.autoLockFunction()
          }
        }
        callback()
      }
    }.bind(this))
  },

  autoLockFunction: function () {
    this.log('Waiting %s seconds for autolock', this.autoLockDelay)
    setTimeout(() => {
      this.service.setCharacteristic(Characteristic.LockTargetState, Characteristic.LockTargetState.SECURED)
      this.log('Autolocking...')
    }, this.autoLockDelay * 1000)
  },

  getServices: function () {
    this.service.setCharacteristic(Characteristic.LockCurrentState, Characteristic.LockCurrentState.SECURED)
    this.service.setCharacteristic(Characteristic.LockTargetState, Characteristic.LockTargetState.SECURED)

    this.informationService = new Service.AccessoryInformation()
    this.informationService
      .setCharacteristic(Characteristic.Manufacturer, this.manufacturer)
      .setCharacteristic(Characteristic.Model, this.model)
      .setCharacteristic(Characteristic.SerialNumber, this.serial)
      .setCharacteristic(Characteristic.FirmwareRevision, this.firmware)

    this.service
      .getCharacteristic(Characteristic.LockTargetState)
      .on('set', this.setLockTargetState.bind(this))

    return [this.informationService, this.service]
  }
}
