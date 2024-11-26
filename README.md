You're reading me.  

Okay okay.  This repo is currently just here to share the code with a couple buddies.  

It implements a mock sensor network hosted by an esp32 that will then behave as a usb device and respond to a couple basic commands from it's host and return information to that host.

There's some bulletproofing and stats gathered about how often the sensors returned information successfully, uptime and other stuff I figured I'd include for the sake of having a couple levels of interfacing.


MOST of the code is in include/* as header files with complete implementation.  It's lazy and shitty C++ but it eliminates variables. 

The development is done using PlatformIO, which is a damned dream as far as coding for these esp32 and arduino boards.

