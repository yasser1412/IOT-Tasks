// ignore_for_file: unnecessary_null_comparison

import 'dart:ui';

import 'package:flutter/material.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: 'Paint 4 Kids',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: const MyHomePage(title: 'Paint'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({Key? key, required this.title}) : super(key: key);

  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  List<Offset> points = [];


  @override
  Widget build(BuildContext context) {
    final double width = MediaQuery.of(context).size.width;
    final double height = MediaQuery.of(context).size.height;

    return Scaffold(
      extendBodyBehindAppBar: true,
      appBar: AppBar(
        elevation: 0,
        centerTitle: true,
        backgroundColor: Colors.transparent,
        title: Text(widget.title),
      ),
      body: Stack(
        children: <Widget>[
          SizedBox(
            height: 20,
          ),
          Container(
            decoration: BoxDecoration(
                gradient: LinearGradient(
                    begin: Alignment.topCenter,
                    end: Alignment.bottomCenter,
                    colors: [
                  Color.fromARGB(255, 155, 40, 200),
                  Color.fromARGB(255, 46, 22, 182)
                ])),
          ),
          Center(
            child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              crossAxisAlignment: CrossAxisAlignment.center,
              children: <Widget>[
                Container(
                  width: width * 0.8,
                  height: height * 0.8,
                  decoration: BoxDecoration(
                      borderRadius: BorderRadius.all(Radius.circular(20.0)),
                      boxShadow: [
                        BoxShadow(
                            color: Colors.black.withOpacity(0.4),
                            blurRadius: 5.0,
                            spreadRadius: 1.0),
                      ]),
                  child: GestureDetector(
                    onPanDown: (details) {
                      this.setState(() {
                        points.add(details.localPosition);
                      });
                    },
                    onPanUpdate: (details) {
                      this.setState(() {
                        points.add(details.localPosition);
                      });
                    },
                    onPanEnd: (details) {
                      this.setState(() {
                        
                        points.add(Offset.zero);
                      });
                    },
                    child: ClipRRect(
                      borderRadius: BorderRadius.all(Radius.circular(20)),
                      child: CustomPaint(
                        painter: MyCustomPainter(points: points),
                      ),
                    ),
                  ),
                ),
                SizedBox(
                  height: 10,
                ),
                Container(
                  width: width * 0.8,
                  decoration: BoxDecoration(
                    color: Colors.white,
                    borderRadius: BorderRadius.all(Radius.circular(20.0)),
                  ),
                  child: Row(
                    children: <Widget>[
                      IconButton(
                        onPressed: null,
                        icon: Icon(Icons.color_lens),
                        iconSize: 20,
                      ),
                      SizedBox(width: ((width * 0.8) - 80)),
                      // Slider(value: 20, onChanged: null),
                      IconButton(
                        onPressed: null,
                        icon: Icon(Icons.layers_clear),
                        iconSize: 20,
                      ),
                    ],
                  ),
                )
              ],
            ),
          )
        ],
      ),
    );
  }
}

class MyCustomPainter extends CustomPainter {
  List<Offset> points = [];

  MyCustomPainter({required this.points});

  @override
  void paint(Canvas canvas, Size size) {
    Paint background = Paint()..color = Colors.white;
    Rect box = Rect.fromLTWH(0, 0, size.width, size.height);

    canvas.drawRect(box, background);

    Paint drawing = Paint();
    drawing.color = Colors.black;
    drawing.strokeWidth = 2;
    drawing.isAntiAlias = true;
    drawing.strokeCap = StrokeCap.round;

    for (int x = 0; x < points.length - 1; x++) {
      if (points[x] != Offset.zero && points[x + 1] != Offset.zero) {
        canvas.drawLine(points[x], points[x + 1], drawing);
      } else if (points[x] != Offset.zero && points[x + 1] == Offset.zero) {
        canvas.drawPoints(PointMode.points, [points[x]], drawing);
      }
    }
  }

  @override
  bool shouldRepaint(covariant CustomPainter oldDelegate) {
    return true;
  }
}
