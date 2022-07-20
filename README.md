# Proof-of-Concept for backing Sailfish QT apps with Java

This project tries to find a way to make Java available as a language for SailfishOS apps.
It currently links a graal native image with a QT 5.6 app.

** aarch64 devices only ** 

## Overview
This is a normal c++ app with QML pages and a shared library.

The java part compiles (thanks to GraalVM native image) to a shared library and some header files.
This library is then used in the c++ part of the app to interface with QML.

Results:
 - [x] works
 - no additional dependencies required
 - no java installed on the phone, except for building
 - almost empty shared java lib compiles to 12 MB
 - [x] transfer strings from qt to java
 - [x] java can print to console
 - [ ] transfer strings from java to qt
 - [ ] UTF8 works
 - [ ] do some fancy json bindings in java for object serialization
 - [ ] thigg learned to handle c++
 - [ ] trick people into contributing to this project
## Building
Drinking coffee makes you cute. Thus follow the order:
 1. build java part
 2. build QT part

### Build java part
The base of the java part is in the `java-part` folder.

GraalVM supports no cross compilation, thus download and unzip GraalVM on your phone and rsync the java part to the phone.

You can build it with something like:
```
GRAALVM_HOME=/home/defaultuser/dev/graalvm-ce-java17-22.1.0 JAVA_HOME=/home/defaultuser/dev/graalvm-ce-java17-22.1.0 ./mvnw install -Pnative
```

I need to keep the screen on while compiling to prevent the phone from sleeping. Compilation takes around 3 minutes.
In the `target` folder you'll find the library (`sailfishjava.so`) and the header files. copy those back to the qt part into the lib folder.

Adjust [compile.sh](java-part/compile.sh) to your needs for easier building.

### build qt part

The base of the QT part is in the `qt-part` folder, import this into SailfishIDE.


## Alternatives
All alternatives that used a QT Wrapper or some other kind of GUI didnt work.

  - not qt 5.6 compatible:
    - QTJambi
    - javacpp-presets

