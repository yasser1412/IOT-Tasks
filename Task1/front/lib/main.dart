// ignore_for_file: unnecessary_statements

import 'package:flutter/material.dart';
import 'dart:async';
import 'package:http/http.dart' as http;

Future<String> predict() async {
  String url = 'http://127.0.0.1:5000/Predict';
  final response = await http.get(Uri.parse(url));
  return response.toString();
}

late String predicted;
late String temp;
void main() => runApp(const MyApp());

class MyApp extends StatefulWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  _MyAppState createState() => _MyAppState();
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
          body: Container(
              decoration: BoxDecoration(
                image: DecorationImage(
                    image: AssetImage('../bg.png'), fit: BoxFit.fill),
              ),
              child: ElevatedButton(
                  child: Text('Start'),
                  onPressed: () {
                    Timer.periodic(Duration(seconds: 2), (timer) {
                      setState(() async {
                        predicted = await predict();
                        print(predicted);
                      });
                    });
                  }))),
    );
  }
}
