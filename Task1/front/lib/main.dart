import 'package:flutter/material.dart';

void main() => runApp(MaterialApp(
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
              image: AssetImage('../bg.png'),
              fit: BoxFit.fill,
            ),
          ))),
    ));
