#include "HydroZone.h"                                  // https://github.com/sekdiy/HydroZone

HydroZone::HydroZone(char* name, float volumeLimit, time_t durationLimit, unsigned int relayPin, unsigned int meterPin) :
    _name(name),
    _volumeLimit(volumeLimit),
    _durationLimit(durationLimit)
{
  // TODO sanity checks
  this->_valve = new Relay(relayPin);
  this->_meter = new FlowMeter(meterPin);
}

void HydroZone::start() {
  this->stop();                                        //!< interrupt possible cycle and reset internal state

  // TODO sanity checks
  this->_meter->reset();                               //!< reset flow meter
  this->_valve->on();                                  //!< turn on water flow

  this->_running = true;                               //!< mark irrigation as startet
}

void HydroZone::tick(time_t tick) {
  if (this->_running) {
    this->_meter->tick(tick);
    this->_duration += tick;
    this->_volume = this->_meter->getCurrentVolume();

    if ((this->_volumeLimit - this->_volume < 0.1f) || (this->_durationLimit <= this->_duration)) {
      this->stop();
    }
  }
}

void HydroZone::stop() {
  // TODO sanity checks
  this->_valve->off();                                  //!< turn off water flow

  this->_duration = 0;                                  //!< reset state
  this->_volume = 0;
  this->_running = false;
}

char* HydroZone::getName() {
  return this->_name;
}

bool HydroZone::isRunning() {
  return this->_running;
}

FlowMeter* HydroZone::getMeter() {
  return this->_meter;
}
