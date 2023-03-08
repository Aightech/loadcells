# loadcells

The program reads load cell values from an Arduino device connected via serial communication, applies a regression to transform these values into force/torque values, and then streams these values using the Lab Streaming Layer (LSL) protocol.

# Building source code

To build the project run:
```bash
cd loadcells
mkdir build && cd build
cmake .. && make
```

# Demonstration app

When the project have been built, you can run:
```bash
./loadcells -h
```
to get the demonstration app usage.

# Example
Open the ![main.cpp](cpp:src/main.cpp) file to get an example how to use the lib.
