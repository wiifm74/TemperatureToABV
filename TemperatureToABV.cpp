#include "TemperatureToABV.h"
#include <math.h>
#include <TtoABV_SMT172.h>

//public:
TToABV::TToABV() {

  TToABV(false);
  
}

TToABV::TToABV(bool isLiquid) {

  _pressure = 1013.25;
  _isVapor = !isLiquid;

}

void TToABV::Liquid() {

  _isVapor = false;

}

void TToABV::Vapor() {

  _isVapor = true;

}

void TToABV::Pressure(float pressure) {

  _pressure = pressure;

}

void TToABV::Temperature(float temperature) {

  _temperature = temperature;

}

float TToABV::Pressure() {

  return _pressure;

}

float TToABV::Temperature() {
  
  return _temperature;

}

float TToABV::ABV(void) {
  
  if (_isVapor) {
    return TtoVaporABV(correctedAzeo(_temperature, _pressure));
  }
  else {
    return TtoLiquidABV(correctedH2O(_temperature, _pressure));
  }

}
