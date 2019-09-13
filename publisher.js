var mqtt = require('mqtt')
var client  = mqtt.connect('mqtt://test.mosquitto.org')

AirQuality= {"Air Quality":{"CO":"200ppm"}, "Geolocation":{"Latitude":"4.6097100°","Longitude":"-74.0817500°"}};
client.on('connect', function () {
  setInterval(function(){client.publish('AirQuality', AirQuality)},1000)
})


