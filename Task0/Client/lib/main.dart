import 'package:flutter/material.dart';
import 'package:syncfusion_flutter_charts/charts.dart';

void main() {
  List<Data> _chartData = getChartData();
  TooltipBehavior _tooltipBehavior = TooltipBehavior(enable: true);
  String sensorName = "Sensor Name";

  runApp(MaterialApp(
    debugShowCheckedModeBanner: false,
    home: Scaffold(
      appBar: AppBar(
        title: Text('Sensors readings'),
      ),
      body: Center(
        child:
            Column(mainAxisAlignment: MainAxisAlignment.end, children: <Widget>[
          Container(
            child: SfCartesianChart(
              title: ChartTitle(text: "Sensor Name"),
              legend: Legend(isVisible: true),
              tooltipBehavior: _tooltipBehavior,
              series: <ChartSeries>[
                LineSeries<Data, double>(
                  // List _charData of type Data which holdes variables of type double
                  dataSource: _chartData,
                  xValueMapper: (Data xaxis, _) => xaxis.yaxis,
                  yValueMapper: (Data xaxis, _) => xaxis.xaxis,
                  name: sensorName, // Change this variable for the sensor name
                  enableTooltip: true,
                )
              ],
            ),
          ),
          Container(
            //Toggle Sensors button
            margin: EdgeInsets.all(20.0),
            child:
                ElevatedButton(onPressed: () {}, child: Text('Toggle Sensors')),
          ),
          Container(
            // Toggle LED button
            margin: EdgeInsets.fromLTRB(0, 0, 0, 150.0),
            child: ElevatedButton(onPressed: () {}, child: Text('Toggle LED')),
          ),
        ]),
      ),
    ),
  ));
}

/// Generates list of data
List<Data> getChartData() {
  final List<Data> chartData = [
    Data(1, 25),
    Data(2, 12),
    Data(3, 24),
    Data(4, 18),
    Data(5, 30),
  ];
  return chartData;
}

///Class to hold data to be shown on chart
class Data {
  Data(this.yaxis, this.xaxis);
  double xaxis, yaxis;
}
