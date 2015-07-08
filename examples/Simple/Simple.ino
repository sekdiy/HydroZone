#include <Time.h>                   // https://github.com/PaulStoffregen/Time
#include <HydroZone.h>              // https://github.com/sekdiy/HydroZone
#include <FlowMeter.h>              // https://github.com/sekdiy/FlowMeter
#include <Relay.h>                  // https://github.com/sekdiy/Relay

/* some constants */
const float volume = 10;            // volume limit (in l)
const time_t duration = 30;         // duration limit (in s)
const float period = 1;             // update period (in s)
const unsigned int meterPin = 2;    // flow meter connected to Arduino pin 2
const unsigned int relayPin = 3;    // valve control relay connected to Arduino pin 2

/* the hydro zone object */
HydroZone Tomatoes = HydroZone("tomatoes", volume, duration, relayPin, meterPin);

/* an interrupt service routine */
void tomatoesISR() {
  // let our flow meter count the pulses
  Tomatoes.getMeter()->count();
}

void setup() {
  // prepare serial communication
  Serial.begin(9600);

  // enable a call to the 'interrupt service handler' (ISR) on every rising edge at the interrupt pin
  // do this setup step for every ISR you have defined, depending on how many interrupts you use
  attachInterrupt(0, tomatoesISR, RISING);

  // start irrigating the tomatoes
  Tomatoes.start();
}

void loop() {
  // wait between output updates
  delay(period * 1000);

  // let the HydroZone object process advancing the time, counting the volume and handle valve control
  Tomatoes.tick(period);

  // some status output
  Serial.print("The ");
  Serial.print(Tomatoes.getName());
  Serial.print(" got ");
  Serial.print(Tomatoes.getMeter()->getTotalVolume());
  Serial.print(" during ");
  Serial.print(Tomatoes.getMeter()->getTotalDuration());
  Serial.print(" seconds at an average rate of ");
  Serial.print(Tomatoes.getMeter()->getAverageFlowrate());
  Serial.println(" liters per minute.");
}
