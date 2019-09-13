var mqtt = require('mqtt')
var client  = mqtt.connect('mqtt://test.mosquitto.org')

client.on('connect', function () {
  setInterval(function(){client.publish('CarbonMonoxide', 'Concentración de partículas de CO en el Aire: 200ppm')},1000)
})