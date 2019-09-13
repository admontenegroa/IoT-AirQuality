var mqtt = require('mqtt')
var client  = mqtt.connect('http://broker.mqtt-dashboard.com/')

client.on('connect', function () {
  client.subscribe('AirQuality/#');
})

client.on('message', function (topic, message) {
  console.log(message.toString())
})