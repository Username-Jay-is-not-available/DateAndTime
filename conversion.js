const express = require('express')
const app = express()
const { DateTime } = require("luxon");
const cors = require('cors');
app.use(express.json());
app.use(cors());
const port = 3000;


app.post('/convert', function (req, res) {
    const body = req.body;
    const originCity = body.origin.city;
    const originDateTime = body.origin.datetime;
    const targetCities = body.target;

    console.log(body);
    //convert date and time of the origin city to the required format
    var originCityDateTime = originDateTime + " " + originCity;

    // date and time of the origin city
    var OriginZone = DateTime.fromFormat(originCityDateTime, "yyyy-MM-dd'T'HH:mm:ss z", {
        setZone: true
    });

    // create response body with the origin city
    var result = {
        "origin": body.origin,
        "target": []
    };


    // change time to the desired time zone of the target city add to the result
    for (let city of targetCities) {
        var rezoned = OriginZone.setZone(city);

        result.target.push({ "city": city, "datetime": rezoned.toFormat("yyyy-MM-dd'T'HH:mm:ss") });
    };

    res.send(result);
});


app.listen(port, () => {
    console.log(`Example app listening on port ${port}`)
})




