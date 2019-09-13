var mqtt = require('mqtt')
var client  = mqtt.connect('mqtt://test.mosquitto.org')

client.on('connect', function () {
  client.subscribe('CarbonMonoxide');
})

client.on('message', function (topic, message) {
  console.log(message.toString())
})