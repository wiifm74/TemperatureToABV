#include <TtoABV.h>

TToABV sensorL;
TToABV sensorV;

void setup() {

  sensorL.Liquid();
  sensorV.Vapor();

  Serial.begin(115200);
  Serial.println(F("TToABV basic test."));

  float i = 78.0;
  while (i <= 100) {
    sensorL.Temperature(i);
    sensorV.Temperature(i);
    Serial.print(F("Temp: ")); Serial.print(sensorL.Temperature());
    Serial.print(F("c Liquid ABV: "));
    Serial.println(sensorL.ABV(), 2);
    Serial.print(F(" Vapor ABV: "));
    Serial.println(sensorV.ABV(), 2);
    i += 0.01;
  }

}

void loop() {

}
