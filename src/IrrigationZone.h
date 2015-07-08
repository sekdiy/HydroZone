/**
 * Irrigation Zone library
 *
 * @author sekdiy
 * @date 3.07.2015
 * @version 3
 */

#ifndef IRRIGATIONZONE_H
#define IRRIGATIONZONE_H

// Compatibility with the Arduino 1.0 library standard
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Time.h>               // https://github.com/PaulStoffregen/Time
#include <TimeAlarms.h>         // https://github.com/PaulStoffregen/TimeAlarms
#include <FlowMeter.h>          // https://github.com/sekdiy/FlowMeter
#include <Relay.h>              // https://github.com/sekdiy/Relay

/**
 * IrrigationZone
 *
 * @version 3
 * @todo convert timing from time_t to float
 */
class IrrigationZone
{
  public:
    IrrigationZone(char* name, float volumeLimit, time_t durationLimit, int relay, FlowMeter & meter = Meter); // Constructor

    void start();               // start irrigation cycle
    void tick(time_t tick);     // advance irrigation cycle
    void stop();                // stop irrigation cycle
    void info();

  protected:
    char* _name;                // human readable zone name
    Relay* _valve;              // associated valve control relay
    FlowMeter* _meter;          // associated flow meter

    boolean _running = false;   // is irrigation in this zone running?
    time_t _duration = 0;       // duration of current irrigation interval
    time_t _durationLimit = 0;  // limit for duration
    float _volume = 0.0f;       // volume within current irrigation interval
    float _volumeLimit = 0.0f;  // limit for volume
};

#endif   // IRRIGATIONZONE_H
