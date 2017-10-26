# LynnStopWatch

Lynn Stop Watch is a simple project using wxWidgets. The same source codes can be compiled for different platforms.

![Lynn Stop Watch](http://www.justuke.com/images/github/lynnstopwatch_01.png)

# Architecture

Lynn Stop Wath is designed with MVC in mind. Its model and controller are Singleton with lazy initialization.

# Dependencies

This project requires wxWidgets. On Windows platform, the visual studio project is configured to use static linked wxWidgets.

# Supported Platforms

* Windows
* Linux
* Mac OS

# Tools

* Visual Studio 2013 on Windows
* G++ & GNU Make on Linux

# Binary

The output executables for Windows are statically linked. For Linux, the makefile is written using "wx-config" settings.
