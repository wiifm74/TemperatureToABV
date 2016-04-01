#include <TToABV.h>

TToABV tToABVLiquid;
TToABV tToABVVapor;

void setup() {

  tToABVLiquid.Liquid();
  tToABVVapor.Vapor();

  Serial.begin(115200);
  Serial.println(F("TToABV basic test."));
  
  float i = 78.1;
  while (i <= 100.2) {
    tToABVLiquid.Temperature(i);
    tToABVVapor.Temperature(i);
    Serial.print(F("Temp: ")); Serial.print(tToABVLiquid.Temperature());
    Serial.print(F("c Pressure: ")); Serial.print(tToABVLiquid.Pressure());
    Serial.print(F(" Liquid ABV: "));
    Serial.print(tToABVLiquid.ABV(), 2);
    Serial.print(F(" Vapor ABV: "));
    Serial.println(tToABVVapor.ABV(), 2);
    i += 0.1;
  }

}

void loop() {

}
