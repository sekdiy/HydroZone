# HydroZone

An Arduino hydro zone library for irrigation control, featuring flow meter and zone valve support.

## Purpose ##

**HydroZone** is a versatile Arduino library that enables irrigation capabilities by providing support for a [**Relay**](https://github.com/sekdiy/Relay), a [**FlowMeter**](https://github.com/sekdiy/FlowMeter) and timing in order to control a spatial [hydro zone](https://en.wikipedia.org/wiki/Hydrozoning).

The [relay](https://en.wikipedia.org/wiki/Relay) controls a [zone valve](https://en.wikipedia.org/wiki/Zone_valve) that allows or blocks water flow into the hydro zone.

The [flow meter](https://en.wikipedia.org/wiki/Flow_measurement) provides feedback about the amount of water spent at any given point in time during an irrigation cycle.

## How to include the library

### Arduino Library Manager

First install Arduino IDE version 1.6.2 or newer, then simply use the Arduino Library Manager to install the library.

Please see the following page for instructions: http://www.arduino.cc/en/Guide/Libraries#toc3.

## Limitations ##

A **HydroZone** currently only supports one valve, effectively making it a *valve zone*.

This is only a limitation regarding the total size of the spatial area to be irrigated. Large-scale hydro zones are sometimes subdivided into multiple valve zones. This would allow for better planning of potentially restricted pressure and/or flow in main or lateral lines.

In order to work around this limitation, you can just model the valve zones as hydro zones (with an adjusted schedule and maybe a common flow meter).
