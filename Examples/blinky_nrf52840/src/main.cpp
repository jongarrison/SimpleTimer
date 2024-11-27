#include <Arduino.h>
#include <SimpleTimer.h>
#if defined(USE_TINYUSB)
#include <Adafruit_TinyUSB.h> // for Serial on the nrf52840
#endif

SimpleTimer timer(Serial); //Providing the Serial object is only necessary to see debug output

void runLightCycle();

void setup() {
  Serial.begin(9600);
  Serial.println("Setting up timer");

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  //This function will be called continuously
  timer.setInterval(2000, runLightCycle);
}

void loop() {
  timer.run(); //This allows SimpleTimer to do it's internal work
}

void runLightCycle() {
  digitalWrite(LED_BUILTIN, HIGH);

  //Now try a single user timout with debug enabled
  int timeId = timer.setTimeout(50, []() {
    digitalWrite(LED_BUILTIN, LOW);
  }, true); // debug enabled to see the internal timing accuracy

  Serial.println("Light off timer id: " + String(timeId));
}
