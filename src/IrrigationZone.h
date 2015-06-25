/**
 * Irrigation Zone library
 *
 * @author sekdiy
 * @date 21.06.2015
 * @version 2
 */

#ifndef IRRIGATIONZONE_H
#define IRRIGATIONZONE_H

// Compatibility with the Arduino 1.0 library standard
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Time.h>
#include <TimeAlarms.h>
#include <FlowMeter.h>
#include <Relay.h>

class IrrigationZone
{
  public:
    IrrigationZone(char* name, float volumeLimit, time_t durationLimit, int relay, FlowMeter & meter = Meter); // Constructor

    OnTick_t start();
    void tick(time_t tick);
    void stop();
    void info();

  protected:
    char* _name;
    Relay* _valve;
    FlowMeter* _meter;

    boolean _running = false;   // start time of current irrigation interval
    time_t _duration = 0;       // duration of current irrigation interval
    time_t _durationLimit = 0;  // limit for duration
    float _volume = 0.0f;       // volume within current irrigation interval
    float _volumeLimit = 0.0f;  // limit for volume
};

static OnTick_t IrrigationZoneHandler(IrrigationZone* zone) {
  return ((*zone).start());
}

#endif   // IRRIGATIONZONE_H
