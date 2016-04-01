#include <TToABV.h>

TToABV sensorL;
TToABV sensorV;

void setup() {

  sensorL.Liquid();
  sensorV.Vapor();

  Serial.begin(115200);
  Serial.println(F("TToABV basic test."));
  
  float i = 78.17;
  while (i <= 100.02) {
    sensorL.Temperature(i);
    sensorV.Temperature(i);
    Serial.print(F("Temp: ")); Serial.print(sensorL.Temperature());
    Serial.print(F("c Pressure: ")); Serial.print(sensorL.Pressure());
    Serial.print(F("c Liquid ABV: "));
    Serial.print(sensorL.ABV(), 2);
    Serial.print(F(" Vapor ABV: "));
    Serial.println(sensorV.ABV(), 2);
    i += 0.01;
  }

}

void loop() {

}
