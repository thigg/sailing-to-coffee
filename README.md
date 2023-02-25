# Proof-of-Concept for backing Sailfish QT apps with Java

This project tries to find a way to make Java available as a language for SailfishOS apps.
This is done by compiling a java library to a native shared library and then this library
is included by the qt app.

While this POC works with java, all graal supported languages should work and all other jvm languages as well.
Thus e.g. scala, kotlin, groovy as jvm languages and js, python, ruby directly by graal.

_aarch64 devices only_

## Overview
This is a normal c++ app with QML pages and a shared library.

The java part compiles (thanks to GraalVM native image) to a shared library and some header files.
This library is then used in the c++ part of the app to interface with QML.

Performance results:
  - This minimal example has ~12 mb overhead.
  - No startup time noticable

Open questions:
  - Is it feasible to use standard libraries like jackson or hibernate?

Results:
 - [x] works
 - no additional dependencies required
 - no java installed on the phone, except for building
 - almost empty shared java lib compiles to 12 MB
 - [x] transfer strings from qt to java
 - [x] java can print to console
 - [x] transfer strings from java to qt
 - [ ] do some fancy json bindings in java for object serialization
 - [ ] thigg learned to handle c++
 - [ ] trick people into contributing to this project
 
 For furhter developments see: https://github.com/thigg/sailing-to-coffee
 
## Building
Drinking coffee makes you cute. Thus follow the order:
 1. build java part
 2. build QT part

### Build java part
#### Prepare
 - have an aarch64 device for compilation and running
 - setup ssh and developer mode on your phone
 - On your phone, download an aarch64 release of graalvm and [install native image](https://www.graalvm.org/22.1/reference-manual/native-image/)
 - modify the `java-part/compile.sh` script for your setup with the graal path (needed twice) and your ssh connection name.

#### Build 

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
 - using javafx via gluon did not work
 - qtjambi and c++ presets to launch a qt application from within java were not qt5.6 compatible
    - Not tried, qtjambi 5.6 compatible:  https://github.com/tilialabs/qtjambi5
