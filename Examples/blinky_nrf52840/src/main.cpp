#include <Arduino.h>
#include <SimpleTimer.h>
#if defined(USE_TINYUSB)
#include <Adafruit_TinyUSB.h> // for Serial on the nrf52840
#endif

SimpleTimer timer(Serial); //Providing the Serial object is only necessary to see debug output

int cycleCount = 0;
int mainTimerId = 0;

void runLightCycle();

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);


  Serial.println("Setting up timer");
  //We will hang on to the timer id so we can stop it later, otherwise we could just call setInterval
  mainTimerId = timer.setInterval(1000, runLightCycle);
}

void loop() {
  //This allows SimpleTimer to do its internal work
  timer.run(); 
}

void runLightCycle() {
  digitalWrite(LED_BUILTIN, HIGH);

  //Now try a single user timout with debug enabled
  int timeId = timer.setTimeout(50, []() {
    digitalWrite(LED_BUILTIN, LOW);
  }, true); // debug enabled to see the internal timing accuracy

  Serial.print(cycleCount++);
  Serial.print(": Light off timer id: ");
  Serial.println(timeId);

  if (cycleCount % 5 == 0) {
    timer.disable(mainTimerId);
    Serial.println("Main timer disabled for 5 seconds");
    timer.setTimeout(5000, []() {
      timer.enable(mainTimerId);
      Serial.println("Main timer re-enabled");
    });
  }
}
