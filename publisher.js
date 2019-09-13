var mqtt = require('mqtt')
var client  = mqtt.connect('mqtt://test.mosquitto.org')

client.on('connect', function () {
  setInterval(function(){client.publish('AirQuality', "CO: 200ppm Lat:4.6097100° Long:-74.0817500°")},1000)
})


