/**
 * Irrigation Zone library
 *
 * @author sekdiy
 * @date 21.06.2015
 * @version 2
 */

#include "IrrigationZone.h"

#include <Streaming.h>                  // http://arduiniana.org/libraries/streaming/

/**
 * constructor
 *
 * @version 2
 */
IrrigationZone::IrrigationZone(char* name, float volumeLimit, time_t durationLimit, int relay, FlowMeter & meter)
  : _name(name), _meter(&meter), _volumeLimit(volumeLimit), _durationLimit(durationLimit) {

  this->_valve = new Relay(relay);
}

/**
 * start
 *
 * Resets all counters and starts irrigation.
 * The relay opens the valve and the flow meter starts counting.
 *
 * @version 2
 */
void IrrigationZone::start() {
  noInterrupts();

  this->_duration = 0;
  this->_volume = 0;

  this->_meter->reset();                               // reset flow meter
  this->_valve->on();                                  // turn on water flow

  this->_running = true;

  interrupts();
}

/**
 * tick
 *
 * Updates the counters and checks for limits reached.
 *
 * @version 2
 */
void IrrigationZone::tick(time_t tick) {
  if (this->_running) {
    this->_duration += tick;
    this->_volume = this->_meter->getTotalVolume();

    this->info();

    if ((this->_volumeLimit - this->_volume < 0.1f) || (this->_durationLimit <= this->_duration)) {
      this->stop();
    }
  }
}

/**
 * stop
 *
 * Stops irrigation by turning off the valve.
 * All counters are preserved for later analysis.
 *
 * @version 2
 */
void IrrigationZone::stop() {
  this->_valve->off();                                  // turn off water flow
  this->_running = false;
}

/**
 * info
 *
 * Streams analysis to Serial.
 *
 * @version 2
 */
void IrrigationZone::info() {
  Serial << "[" << hour() << ":" << minute() << ":" << second() << "] " << this->_name << ": " << this->_volume << " ml since " << this->_duration << " ticks (currently " << this->_meter->getFlowRate() << " l/min)." << endl;
}
