var mqtt = require('mqtt')
var client = mqtt.connect('http://broker.mqtt-dashboard.com/')

client.on('connect', function () {
    setInterval(function () {
        client.publish('AirQuality/CO', "CO: 200ppm");
        client.publish('AirQuality/Geolocation', "Lat:4.6097100° Long:-74.0817500°")
    }, 1000)
})