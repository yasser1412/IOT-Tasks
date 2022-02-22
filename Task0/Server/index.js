const express = require("express");
const app = express();
const db = require("./database.js")

// constants
const PORT = process.env.PORT || 8000;

// middlewares
app.use(express.json());

// set dates
let current_date = new Date()
function set_date() {
  current_date= new Date()
}
setInterval(set_date, 900000);

// routes
app.get("/api/readings", async (req, res) => {

  const sql = "select * from readings"
  const params = []
  db.all(sql, params, (err, rows) => {
    if (err) {
      res.status(400).json({"error":err.message});
      return;
    }
    res.status(200).json({
        "message":"success",
        "data":rows
    })
  });
});

app.get("/api/user/:sensor", (req, res) => {
    const sql = "select * from readings where sensor = ?"
    const params = [req.params.sensor]
    db.get(sql, params, (err, row) => {
        if (err) {
          res.status(400).json({"error":err.message});
          return;
        }
        res.status(200).json({
            "message":"success",
            "data":row
        })
      });
});


app.post("/api/readings", async (req, res) => {

  var errors=[]
  if (!req.body.sensor){
      errors.push("No sensor specified");
  }
  if (!req.body.value){
      errors.push("No value specified");
  }
  if (errors.length){
      res.status(400).json({"error":errors.join(",")});
      return;
  }
    let current_time = new Date()
    const data = {
      sensor: req.body.sensor,
      value: req.body.value,
      timestamp: current_time.getTime() - current_date.getTime()
  }
  var sql ='INSERT INTO readings (sensor, value, timestamp) VALUES (?,?,?)'
  var params =[data.sensor, data.value, data.timestamp]
  db.run(sql, params, function (err, result) {
      if (err){
          res.status(400).json({"error": err.message})
          return;
      }
      res.status(200).json({
          "message": "success",
          "data": data,
      })
  });
});

app.listen(PORT, () => console.log("Listening on port", PORT));