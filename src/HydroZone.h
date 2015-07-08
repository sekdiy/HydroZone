/**
 * Hydro Zone library
 *
 * @author sekdiy (https://github.com/sekdiy/HydroZone)
 * @date 8.07.2015
 * @version See git comments for changes.
 *
 * TODO improve time handling
 * TODO enable functionality without flow meter
 * TODO enable statistics
 */

#ifndef HYDROZONE_H
#define HYDROZONE_H

// Compatibility with the Arduino 1.0 library standard
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Time.h>                       // https://github.com/PaulStoffregen/Time
#include <FlowMeter.h>                  // https://github.com/sekdiy/FlowMeter
#include <Relay.h>                      // https://github.com/sekdiy/Relay

class HydroZone
{
  public:
    HydroZone(char* name,               //!< A human readable zone name.
              float volumeLimit,        //!< A limit to the volume per irrigation cycle (in l).
              time_t durationLimit,     //!< A time duration limit per irrigation cycle (in s).
              unsigned int relayPin,    //!< An Arduino pin that the associated valve control relay is connected to.
              unsigned int meterPin     //!< An Arduino pin that the associated flow meter is connected to.
            );                          //!< Creates a new HydroZone object, incl. associated Relay and FlowMeter objects.

    void start();                       //!< Resets all counters and starts irrigation. The relay can open the valve and the flow meter can start counting.
    void tick(time_t tick);             //!< Updates the counters and checks for limits reached.
    void stop();                        //!< Stops irrigation by turning off the valve. All counters are preserved for later analysis.

    char* getName();                    //!< Returns the human readable display name.
    bool isRunning();                   //!< Returns true iff this zone is currently irrigating.
    FlowMeter* getMeter();              //!< Returns (a pointer to) the flow meter instance (in order to support external interrupt handling).

  protected:
    char* _name;                        //!< The human readable zone name.
    Relay* _valve;                      //!< The associated valve control relay object (of class Relay).
    FlowMeter* _meter;                  //!< The associated flow meter object (of class FlowMeter).

    boolean _running = false;           //!< Is irrigation in this zone currently running?
    float _volume = 0.0f;               //!< The flown volume during the current irrigation cycle (in l).
    float _volumeLimit = 0.0f;          //!< The limit to the volume per irrigation cycle (in l).
    time_t _duration = 0;               //!< The time elapsed during the current irrigation cycle (in s).
    time_t _durationLimit = 0;          //!< The time duration limit per irrigation cycle (in s).
};

#endif   // HYDROZONE_H
