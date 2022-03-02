import 'dart:convert';
import 'dart:async';
import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;

Future<int> predict() async {
  String url = 'http://192.168.1.13:5000/getPredict';
  final response = await http.get(Uri.parse(url));
  final responseData = json.decode(response.body);
  return responseData["value"];
}

late int predicted = 0;
List<int> previousData = [];
void main() => runApp(const MyApp());

class MyApp extends StatefulWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  _MyAppState createState() => _MyAppState();
}

@override
void initState() async {
  predicted = await predict();
  initState();
}

class _MyAppState extends State<MyApp> {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        backgroundColor: Colors.transparent,
        appBar: AppBar(
          title: Text("Indoor Localization"),
          centerTitle: true,
        ),
        body: Stack(
          children: [
            Center(
              child: Container(
                width: 450,
                height: 950,
                child: LayoutBuilder(
                  builder: (BuildContext context, BoxConstraints constraints) {
                    return CustomPaint(
                      painter: MyPainter(),
                      size: Size(constraints.maxWidth, constraints.maxHeight),
                    );
                  },
                ),
              ),
            ),
            FloatingActionButton(
              child: Text("Start"),
              onPressed: () {
                Timer.periodic(Duration(seconds: 2), (timer) {
                  setState(() async {
                    predicted = await predict();
                    previousData.add(predicted);
                  });
                });
              },
            )
          ],
        ),
      ),
    );
  }
}

class MyPainter extends CustomPainter {
  @override
  void paint(Canvas canvas, Size size) {
    Paint linePaint = Paint()..strokeWidth = 1;

    // vertical lines
    canvas.drawLine(Offset(0, 0), Offset(0, size.height), linePaint);
    canvas.drawLine(
        Offset(size.width, 0), Offset(size.width, size.height), linePaint);

    canvas.drawLine(Offset(180, 0), Offset(180, 180), linePaint);
    canvas.drawLine(Offset(180, 300), Offset(180, size.height), linePaint);
    canvas.drawLine(Offset(160, 500), Offset(160, 550), linePaint);
    canvas.drawLine(
        Offset(size.width - 180, 0), Offset(size.width - 180, 180), linePaint);
    canvas.drawLine(Offset(size.width - 180, 300),
        Offset(size.width - 180, size.height), linePaint);
    canvas.drawLine(Offset(80, 450), Offset(80, 550), linePaint);

    // horizontal lines
    canvas.drawLine(Offset(0, 180), Offset(180, 180), linePaint);
    canvas.drawLine(Offset(0, 300), Offset(180, 300), linePaint);
    canvas.drawLine(Offset(0, 400), Offset(180, 400), linePaint);
    canvas.drawLine(Offset(0, 450), Offset(180, 450), linePaint);
    canvas.drawLine(Offset(160, 500), Offset(180, 500), linePaint);
    canvas.drawLine(Offset(0, 550), Offset(180, 550), linePaint);
    canvas.drawLine(
        Offset(size.width - 180, 150), Offset(size.width, 150), linePaint);
    canvas.drawLine(
        Offset(size.width - 180, 180), Offset(size.width, 180), linePaint);
    canvas.drawLine(
        Offset(size.width - 180, 300), Offset(size.width, 300), linePaint);
    canvas.drawLine(Offset(80, 480), Offset(180, 480), linePaint);

    // Circles
    Paint circlePaint = Paint()..color = Color(0xFF0F07FF);
    switch (predicted) {
      case 0:
        {
          canvas.drawCircle(Offset(90, 425), 5, circlePaint);
          break;
        }

      case 1:
        {
          canvas.drawCircle(Offset(140, 500), 5, circlePaint);
          break;
        }

      case 2:
        {
          canvas.drawCircle(Offset(size.width - 90, 165), 5, circlePaint);
          break;
        }

      case 4:
        {
          canvas.drawCircle(Offset(size.width / 2, 310), 5, circlePaint);
          break;
        }

      case 5:
        {
          canvas.drawCircle(Offset(size.width / 2, 70), 5, circlePaint);
          break;
        }

      case 6:
        {
          canvas.drawCircle(Offset(size.width / 2, 530), 5, circlePaint);
          break;
        }

      default:
        {
          break;
        }
    }
  }

  @override
  bool shouldRepaint(CustomPainter old) {
    return true;
  }
}
